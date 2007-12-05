/***************************************************************************
                          md_stream.cpp  -  Insert description
                             -------------------
    begin                : July 13, 2007
    copyright          : (C) 2007 by Giuseppe D'Aqui'
    email                : giuseppe.da@gmail.com
 ***************************************************************************/

/***************************************************************************
 *                                                                                                                 
 *   This program is free software; you can redistribute it and/or modify  
 *   it under the terms of the GNU General Public License, Version 2,        
 *   as published by the Free Software Foundation.                                  
 *                                                                                                                 
 ***************************************************************************/

#include "md_stream.h"
#include <vector>
#include "descriptor.h"
#include "../../common/dir/abstract_directory.h"
#include "../../common/dir/directory_factory.h"

MDStream::MDStream():m_is_empty(true),m_is_inited(false) {}

MDStream::MDStream(std::string stream_id, Uint8 n_flows, Uint32 sequence_size):m_is_empty(true),m_is_inited(false) {
	init(stream_id, n_flows, sequence_size);
}

void MDStream::init(std::string stream_id, Uint8 n_flows, Uint32 sequence_size) 
{
	m_stream_id = stream_id;
	m_stream.resize(n_flows);
	for(Uint32 i=0; i<n_flows; i++)
		m_stream[i].resize(sequence_size);
	m_valid_descriptor.resize(n_flows);
	for(Uint8 k=0; k<n_flows; k++)
		m_valid_descriptor[k].resize(sequence_size, false);
	m_is_inited = true;
}

bool MDStream::get_descriptor(Uint8 flow, Uint32 sequence, Descriptor* &descriptor) const {
	if(m_valid_descriptor[flow][sequence]) {
		descriptor = m_stream[flow][sequence];
		return true;
	}
	return false;
}

Uint32 MDStream::get_sequences_number() const {
	Uint32 max_sequence = 0;
	for (Uint8 i=0; i<m_valid_descriptor.size(); i++)
		if (m_valid_descriptor[i].size() > max_sequence)
			max_sequence = m_valid_descriptor[i].size();
	return max_sequence;
}

Uint8 MDStream::get_flows_number() const {return m_valid_descriptor.size();}

void MDStream::set_descriptor(Descriptor* descriptor) {
	m_is_empty = false;
	Uint8 flow = descriptor->get_flow_id();
	Uint32 sequence = descriptor->get_sequence_number();
	m_stream[flow][sequence] = descriptor;
	m_valid_descriptor[flow][sequence] = true;
}

std::string MDStream::get_name() const {return m_name;}
std::string MDStream::get_stream_id() const {return m_stream_id;}

MDStream::~MDStream() {
	if ((m_is_inited) && (!m_is_empty)) {
		for (Uint32 i=0; i<m_valid_descriptor.size(); i++) {
			for (Uint32 k=0; k<m_valid_descriptor[i].size(); k++) {
				if (m_valid_descriptor[i][k]) {
					delete m_stream[i][k];
				}
			}
		}
	}
}

bool MDStream::load_from_disk(const std::string& path) {
	DataChunk data;
	AbstractDirectory* dir = DirectoryFactory::createDirectory();
	if (dir->load_file(path, data)) {
		deserialize(data);
		LOG_INFO("Loaded MD Stream "<<m_name<<" from "<<path.c_str());
		return true;
	}
	return false;
}

bool MDStream::save_to_disk(const std::string& path) {
	DataChunk data;
	data += serialize();
	AbstractDirectory* dir = DirectoryFactory::createDirectory();
	if (dir->save_file(path, data)) {
		LOG_INFO("Saved MD Stream "<<m_name<<" in "<<path.c_str());
		return true;
	}
	return false;
}

DataChunk& MDStream::serialize() const {
	DataChunk* result = new DataChunk();
	DataChunk temp;
	Uint8 flows_number = m_stream.size();
	Uint32 sequence_size = m_stream[0].size();
	result->append(m_stream_id.c_str());
	result->append(flows_number);
	result->append(sequence_size);
	for (Uint8 flow=0; flow<flows_number; flow++)
		for (Uint32 sequence=0; sequence<sequence_size; sequence++)
			if (m_valid_descriptor[flow][sequence]==true)
			{
				//LOG_INFO("Writing descriptor ("<<flow<<", "<<sequence<<")");
				temp.erase();
				Descriptor* current_descriptor = m_stream[flow][sequence];
				temp += (*current_descriptor).serialize();
				Uint16 descriptor_size = temp.get_lenght();
				result->append(descriptor_size);
				result->operator+=(temp);
			}
	return *result;
}

void MDStream::deserialize(const DataChunk& data) {
	if (data.get_lenght() > 0) {
		DataChunk* temp_dc = new DataChunk();
		temp_dc->operator +=(data);
		char* stream_id;
		temp_dc->extract_head(stream_id);

		Uint8 flows_number;
		temp_dc->extract_head(flows_number);
		Uint32 sequences_number;
		temp_dc->extract_head(sequences_number);
		init(stream_id, flows_number, sequences_number);
		while(temp_dc->get_lenght()>0)
		{
			Uint16 descriptor_size;
			temp_dc->extract_head(descriptor_size);
			Uint8* current_descriptor;
			temp_dc->extract_head(descriptor_size, current_descriptor);
			DataChunk* temp_curr_descriptor = new DataChunk();
			temp_curr_descriptor->append(descriptor_size, current_descriptor);
			Descriptor* d = new Descriptor();
			d->deserialize(*temp_curr_descriptor);
			set_descriptor(d);
		}
	}
}

bool MDStream::is_empty() const {return m_is_empty;}

bool MDStream::is_valid(Uint8 flow, Uint32 sequence) const {
	return (m_valid_descriptor[flow][sequence]);
}


MDStreamInfo MDStream::get_info()
{
	MDStreamInfo info;
	info.stream_id = get_stream_id();
	info.flows_number = get_flows_number();
	info.descriptors_number = get_sequences_number();
	
	return info;
}

