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
#include <string>
#include "defs.h"
#include <vector>
#include "../../common/data_chunk.h"
#include <cassert>
#include "../../common/dir/abstract_directory.h"
#include "../../common/dir/directory_factory.h"

TextStream::TextStream() {m_last_current_position = 0;}

bool TextStream::load_from_disk(const std::string& path) {
	if (path.size() > 0) {
		AbstractDirectory* dir = DirectoryFactory::createDirectory();
		DataChunk dc;
		if (dir->load_file(path, dc)) {
			while (dc.get_lenght() > 0) {
				Uint8 curr_char;
				dc.extract_head(curr_char);
				m_data.push_back((Sint8)curr_char);
			}
			this->m_stream_name = dir->get_filename(path);
			this->m_hash = dir->get_hash_md5(path);
			this->m_last_current_position = 0;
			return true;
		}
	}
	return false;
}

bool TextStream::save_to_disk(const std::string& path) {
	if (path.size() > 0) {
		AbstractDirectory* dir = DirectoryFactory::createDirectory();
		DataChunk dc;
		for (Uint32 i=0; i<m_data.size(); i++)
			dc.append(m_data.at(i));
		if (dir->save_file(path, dc))
			return true;
	}
	return false;
}

Uint32 TextStream::get_last_current_position() const {return m_last_current_position;}

DataChunk& TextStream::get_data(Uint16 dimension) {
	DataChunk* d = new DataChunk();
	if (m_last_current_position+dimension < m_data.size()) {
		for (Uint32 i=m_last_current_position; i<(m_last_current_position+dimension); i++) {
			Sint8 curr_char = m_data[i];
			d->append(curr_char);
		}
		m_last_current_position += dimension;
	}
	else {
		for (Uint32 i=m_last_current_position; i < m_data.size(); i++) {
			Sint8 curr_char = m_data[i];
			d->append(curr_char);
		}
		m_last_current_position = m_data.size()-1;
	}
	return *d;
}

Uint32 TextStream::get_data_dim() const {return m_data.size();}

void TextStream::set_stream_name(std::string& name) {
	if (name.size() > 0)
		m_stream_name = name;
}

std::string TextStream::get_stream_name() const {return m_stream_name;}
void TextStream::update_stream_hash() {m_hash = "livent rulez";}
std::string TextStream::get_stream_hash() const {return m_hash;}
TextStream::~TextStream() {}
