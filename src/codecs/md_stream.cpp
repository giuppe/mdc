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
#include <cassert>
#include "descriptor.h"
#include "../common/dir/abstract_directory.h"
#include "../common/dir/directory_factory.h"

MDStream::MDStream():m_is_empty(true),m_is_inited(false) {}

MDStream::MDStream(Uint8 n_flows, Uint32 sequence_size):m_is_empty(true),m_is_inited(false) {
	init(n_flows, sequence_size);
}

void MDStream::init(Uint8 n_flows, Uint32 sequence_size) {
	m_stream.resize(n_flows);
	for(Uint32 i=0; i<n_flows; i++) {
		m_stream[i].resize(sequence_size);
		for(Uint32 k=0; k<sequence_size; k++)
			m_stream[i][k] = new Descriptor();
	}
	m_valid_descriptor.resize(n_flows);
	for(Uint8 i=0; i<n_flows; i++)
		m_valid_descriptor[i].resize(sequence_size, false);
	m_is_inited = true;
}

bool MDStream::get_descriptor(Uint8 flow, Uint32 sequence, Descriptor* &descriptor) const {
	if(m_valid_descriptor[flow][sequence]) {
		descriptor = m_stream[flow][sequence];
		return true;
	}
	return false;
}

void MDStream::set_descriptor(Descriptor* descriptor) {
	m_is_empty = false;
	Uint8 flow = descriptor->get_flow_id();
	Uint32 sequence = descriptor->get_sequence_number();
	m_stream[flow][sequence] = descriptor;
	m_valid_descriptor[flow][sequence] = true;
	m_name = descriptor->get_file_name();
	m_hash = descriptor->get_hash();
}

std::string MDStream::get_name() const {return m_name;}
std::string MDStream::get_hash() const {return m_hash;}

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
	if(dir->load_file(path, data)) {
		//ulteriori analisi su data
		assert(!"Function is a stub - you should fill it up!");
		return true;
	}
	return false;
}

bool MDStream::save_to_disk(const std::string& path) {
	DataChunk data;
	data += this->serialize();
	AbstractDirectory* dir = DirectoryFactory::createDirectory();
	if(dir->save_file(path, data)) {
		LOG_INFO("Saved MD Stream "<<m_name<<" in "<<path.c_str());
		return true;
	}
	return false;
}

DataChunk& MDStream::serialize() const {
	DataChunk* dc = new DataChunk();
	dc->append(Uint8(m_stream.size()));
	dc->append(Uint32(m_stream[0].size()));
	Uint32 valid_descriptors_number = 0;
	std::vector<std::vector<Descriptor*> > temp_stream;
	temp_stream.resize(m_stream.size());
	for (Uint8 i=0; i<temp_stream.size(); i++)
		temp_stream[i].resize(m_stream[i].size());
	for (Uint8 flow=0; flow<m_stream.size(); flow++)
		for (Uint32 sequence=0; sequence<m_stream[flow].size(); sequence++)
			if (m_valid_descriptor[flow][sequence]) {
				valid_descriptors_number++;
				temp_stream[flow][sequence] = m_stream[flow][sequence];
			}
	dc->append(valid_descriptors_number);
	if (valid_descriptors_number > 0)
		for (Uint8 flow=0; flow<temp_stream.size(); flow++)
			for (Uint32 sequence=0; sequence<temp_stream[flow].size(); sequence++) {
				Descriptor* current_descriptor = new Descriptor();
				current_descriptor = temp_stream[flow][sequence];
				dc->operator +=(*current_descriptor->get_payload());//non accoda il payload
			}
	return *dc;
}

void MDStream::deserialize(const DataChunk& data) {assert(!"This function is a stub.");}
bool MDStream::is_empty() const {return m_is_empty;}
