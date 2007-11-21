/***************************************************************************
           pcx_stream.cpp  - Insert PCX Stream   
                             -------------------
    begin                : Oct 31, 2007
    copyright            : Ivan Coppa
    email                : ivan.coppa@gmail.com
 ***************************************************************************/

/***************************************************************************
 *                                                                                                                 
 *   This program is free software; you can redistribute it and/or modify  
 *   it under the terms of the GNU General Public License, Version 2,        
 *   as published by the Free Software Foundation.                                  
 *                                                                                                                 
 ***************************************************************************/


#include "pcx_stream.h"
#include <string>
#include "defs.h"
#include <vector>
#include "../../common/data_chunk.h"
#include <cassert>
#include "../../common/dir/abstract_directory.h"
#include "../../common/dir/directory_factory.h"

PcxStream::PcxStream()
{
	m_data.resize(0);
}




bool PcxStream::load_from_disk(const std::string& path)
{
	LOG_INFO("Open File\n");
	if (path.size() > 0) {
		AbstractDirectory* dir = DirectoryFactory::createDirectory();
		DataChunk dc;
		if (dir->load_file(path, dc)) {
			while (dc.get_lenght() > 0) {
				Uint8 curr_char;
				dc.extract_head(curr_char);
				m_data.push_back((Sint8)curr_char);
			}
			m_stream_name = dir->get_filename(path);
			m_hash = dir->get_hash_md5(path);
			return true;
		}
	}
	LOG_ERROR("Unable to load pcx stream from "<<path);
	return false;
}




bool PcxStream::save_to_disk(const std::string& path) const
{
	if (path.size()>0 && m_data.size()>0) {
		AbstractDirectory* dir = DirectoryFactory::createDirectory();
		DataChunk dc;
		Uint8* buffer = new Uint8[m_data.size()];
		for (Uint32 i=0; i<m_data.size(); i++)
			buffer[i]= m_data[i];
		dc.append(m_data.size(), buffer);
		if (dir->save_file(path, dc)) return true;
	}
	LOG_ERROR("Unable to write pcx stream to "<<path);
	return false;
}




DataChunk& PcxStream::get_data(Uint64 offset, Uint64 size) const
{
	DataChunk* d = new DataChunk();
	Uint8* buffer = new Uint8[size];
	for(Uint64 i=0; i<size; i++)
	{
		buffer[i]=m_data[offset+i];
		//DEBUG_OUT(Uint32 (offset+i)<<": "<<buffer[i]<<"\n");
	}
	d->append(size, buffer);
	delete[] buffer;
	return *d;
}




Uint32 PcxStream::get_data_dim() const 
{
	return m_data.size();
}




void PcxStream::set_stream_name(std::string& name)
{
	if (name.size() > 0)
		m_stream_name = name;
}




std::string PcxStream::get_stream_name() const 
{
	return m_stream_name;
}




void PcxStream::update_stream_hash() 
{
	m_hash = "livent rulez";
}




std::string PcxStream::get_stream_hash() const 
{
	return m_hash;
}




PcxStream::~PcxStream() {}




void PcxStream::set_data (DataChunk& data) 
{
	Uint32 real_data_size = data.get_lenght();
	m_data.resize(real_data_size);
	Uint8* real_data = data.get_data();
	for (Uint32 i=0; i<data.get_lenght(); i++)
		m_data[i] = real_data[i];
}
