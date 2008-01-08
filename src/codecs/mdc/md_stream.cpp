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

#include "descriptor.h"
#include "../../common/dir/abstract_directory.h"
#include "../../common/dir/directory_factory.h"

MDStream::MDStream():m_is_empty(true),m_is_inited(false) {}

MDStream::MDStream(string stream_id, Uint8 n_flows, Uint32 sequence_size):m_is_empty(true),m_is_inited(false) {
	init(stream_id, n_flows, sequence_size);
}

void MDStream::init(string stream_id, Uint8 n_flows, Uint32 sequence_size) 
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

//string MDStream::get_name() const {return m_name;}


string MDStream::get_stream_id() const {return m_stream_id;}

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

bool MDStream::load_from_disk(const string& path) {
	FileDataChunk data;
	AbstractDirectory* dir = DirectoryFactory::createDirectory();
	if (dir->load_file(path, data)) {
		deserialize(&data);
		LOG_INFO("Loaded MD Stream from "<<path.c_str());
		return true;
	}
	LOG_ERROR("Cannot load MD stream from "<<path);
	return false;
}

bool MDStream::save_to_disk(const string& path) {
	MemDataChunk* data;
	data = &serialize();
	AbstractDirectory* dir = DirectoryFactory::createDirectory();
	bool save_result = dir->save_file(path, data);
	delete data;
	if (save_result == true) {
		LOG_INFO("Saved MD Stream in "<<path.c_str());
		
		return true;
	}
	
	LOG_ERROR("Cannot save MD stream to "<<path);
	return false;
}

MemDataChunk& MDStream::serialize() const {
	MemDataChunk* result = new MemDataChunk();
	MemDataChunk temp;
	Uint8 flows_number = m_stream.size();
	Uint32 sequence_size = m_stream[0].size();
	MemDataChunk temp_stream_id; 
	temp_stream_id.append_cstring(m_stream_id.c_str());
	result->append_data(32, temp_stream_id.get_data());
	result->append_Uint8(flows_number);
	result->append_Uint32(sequence_size);
	for (Uint8 flow=0; flow<flows_number; flow++)
	{
		for (Uint32 sequence=0; sequence<sequence_size; sequence++)
		{
			if (m_valid_descriptor[flow][sequence]==true)
			{
				LOG_INFO("Writing descriptor ("<<flow<<", "<<sequence<<")");
				temp.erase();
				Descriptor* current_descriptor = m_stream[flow][sequence];
				MemDataChunk* curr_desc_serialized = &(*current_descriptor).serialize(); 
				temp += curr_desc_serialized;
				delete curr_desc_serialized;
				Uint16 descriptor_size = temp.get_lenght();
				result->append_Uint16(descriptor_size);
				result->operator+=(&temp);
			}
			else
			{
				LOG_WARN("non-valid descriptor ("<<flow<<", "<<sequence<<"), not serializing");
			}
		}
	}
	return *result;
}

bool MDStream::deserialize(const IDataChunk* data) {
	if (data->get_lenght() == 0) 
	{
		return false;
	}

	DataChunkIterator temp_dc = data->get_iterator();

	Uint8* stream_id= new Uint8[33];
	memset(stream_id, 0, 33);
	if(!temp_dc.get_data(32, stream_id))
	{
		return false;
	}

	Uint8 flows_number;
	if(!temp_dc.get_Uint8(flows_number))
	{
		return false;
	}

	Uint32 sequences_number;
	if(!temp_dc.get_Uint32(sequences_number))
	{
		return false;
	}

	init((char*)stream_id, flows_number, sequences_number);

	while(temp_dc.has_next())
	{
		Uint16 descriptor_size;
		if(!temp_dc.get_Uint16(descriptor_size))
		{
			return false;
		}
		IDataChunk* current_descriptor;
		if(!temp_dc.get_data_chunk((Uint32)descriptor_size, current_descriptor))
		{
			return false;
		}
		Descriptor* d = new Descriptor();
		if(!d->deserialize(current_descriptor))
		{
			return false;
		}
		delete current_descriptor;
		set_descriptor(d);
	}
	return true;

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

