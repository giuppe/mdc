/***************************************************************************
                     text_stream.cpp  -  Insert text stream
                             -------------------
    begin                : Oct 5, 2007
    copyright            : Livio Pipitone
    email                : livent@tiscalinet.it
 ***************************************************************************/

/***************************************************************************
 *                                                                                                                 
 *   This program is free software; you can redistribute it and/or modify  
 *   it under the terms of the GNU General Public License, Version 2,        
 *   as published by the Free Software Foundation.                                  
 *                                                                                                                 
 ***************************************************************************/

#include "text_stream.h"

#include "defs.h"

#include "../../common/data/mem_data_chunk.h"
#include <cassert>
#include "../../common/dir/abstract_directory.h"
#include "../../common/dir/directory_factory.h"
#include "../../common/hash/hash.h"

TextStream::TextStream() {m_data.resize(0);}

bool TextStream::load_from_disk(const string& path) {
	if (path.size() > 0) {
		m_stream_name = path.substr(path.find_last_of("/")+1, path.find_last_of("."));
		AbstractDirectory* dir = DirectoryFactory::createDirectory();
		FileDataChunk dc;
		bool loaded = dir->load_file(path, dc);
		if (loaded) {
			deserialize(&dc);
			return true;
		}
	}
	return false;
}

bool TextStream::save_to_disk(const string& path) const
{
	if (path.size()>0 && m_data.size()>0) {
		AbstractDirectory* dir = DirectoryFactory::createDirectory();
		if (dir->save_file(path, &(this->serialize()))) return true;
	}
	return false;
}

MemDataChunk& TextStream::get_data(Uint64 offset, Uint64 size) const {
	MemDataChunk* d = new MemDataChunk();
	Uint8* buffer = new Uint8[size];
	for(Uint64 i=0; i<size; i++)
		buffer[i]=m_data[offset+i];
	d->append_data(size, buffer);
	delete[] buffer;
	return *d;
}

Uint32 TextStream::get_data_dim() const 
{
	return m_data.size();
}




void TextStream::set_stream_name(string& name) 
{
	if (name.size() > 0)
		m_stream_name = name;
}




string TextStream::get_stream_name() const 
{
	return m_stream_name;
}

MemDataChunk& TextStream::serialize() const {
	MemDataChunk* dc = new MemDataChunk();
	Uint8* buffer = new Uint8[m_data.size()];
	for (Uint32 i=0; i<m_data.size(); i++)
		buffer[i]= m_data[i];
	Uint32 size = m_data.size();
	dc->append_data(size, buffer);
	return *dc;			
}

bool TextStream::deserialize(const IDataChunk* datachunk) {
	DataChunkIterator dc = datachunk->get_iterator();

	while (dc.has_next()) {
		Sint8 curr_char;
		dc.get_Sint8(curr_char);
		m_data.push_back(curr_char);
	}
	return true;
}


string TextStream::compute_hash_md5() const 
{
	return Hash::md5_from_datachunk(this->serialize());
}




TextStream::~TextStream() {}




void TextStream::set_data (MemDataChunk& data) 
{
	Uint32 real_data_size = data.get_lenght();
	m_data.resize(real_data_size);
	Uint8* real_data = data.get_data();
	for (Uint32 i=0; i<data.get_lenght(); i++)
		m_data[i] = real_data[i];
}
