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
#include "../sha/mhash.h"
#include "../common/data_chunk.h"

bool TextStream::load_from_disk(const std::string& path) {
	FILE *m_f;
	char c;
	if (fopen(path.c_str(), "r") != NULL) {
		m_f = fopen(path.c_str(), "r");
		while (fscanf(m_f, "%c", &c) > 0) {
			m_data.push_back(c);
		}
		fclose(m_f);
		m_last_current_position = 0;
		this->update_stream_hash();
		m_stream_name = path.substr(path.find_last_of("/")+1, path.find_last_of(".")-1);
		return true;
	}
	else return false;
}

void TextStream::set_last_current_position(Uint32 new_position) {
	if (m_last_current_position+new_position < m_data.size()-1)
		m_last_current_position = new_position;
}

Uint32 TextStream::get_last_current_position() const {
	return m_last_current_position;
}

DataChunk& TextStream::get_data(Uint16 dimension) const {
	if (!m_data.empty()) {
		DataChunk* d = new DataChunk;
		for (Uint32 i=m_last_current_position; i <  m_last_current_position+dimension; i++)
			d->append(m_data.at(m_last_current_position));
		return *d;
	}
}

Uint32 TextStream::get_data_dim() const {
	return m_data.size();
}

void TextStream::set_stream_name(std::string& name) {
	m_stream_name = name;
}

std::string TextStream::get_stream_name() const {
	return m_stream_name;
}

void TextStream::set_payload_size(Uint32 psize) {
	m_size = psize;
}

void TextStream::update_stream_hash() {
	m_td = mhash_init();
	//m_td = mhash_init(MHASH_SHA1);
	if (m_td == MHASH_FAILED) return;
	else {
		for (Uint32 i=0; i<m_data.size(); i++)
			mhash();
			//mhash(m_td, m_data.at(i), 1);
		//m_hash = mhash_end();
	}
}

std::string TextStream::get_stream_hash() const {
	return m_hash;
}
