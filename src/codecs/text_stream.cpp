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
#include <string.h>
#include "defs.h"
#include <vector>
#include "../sha/mhash_sha1.h"

bool TextStream::load_from_disk(const std::string& path) {
	FILE *m_f;
	char c;
	if (fopen(path.c_str(), "r") != NULL) {
		m_f = fopen(path.c_str(), "r");
		while (fscanf(m_f, "%c", &c) > 0) {
			m_data.push_back(c);
		}
		fclose(m_f);
		return true;
	}
	else return false;
}

char TextStream::get_data(Uint32 init_position, Uint32 final_position) const
{
	if ((!m_data.empty()) && (position <= m_data.size()))
		return m_data.at(position);
	else return NULL;
}

Uint32 TextStream::get_data_dim() const {
	return m_data.size();
}

void TextStream::set_stream_name(std::string& name) {
	m_stream_name = name;
}

std::string& TextStream::get_stream_name() const {
	m_stream_name = path.substr(find_last_of(/)+1, find_last_of(.)-1);
	return m_stream_name;
}

void TextStream::set_payload_size(Uint32 psize) const {
	m_size = psize;
}

Uint32 TextStream::get_payload_size() {
	return m_size;
}

void TextStream::set_current_position(Uint32 new_position) {
	if (m_current_position+new_position < m_data.size()-1)
		m_current_position = new_position;
}

Uint32 TextStream::get_current_position() {
	return m_current_position;
}

void TextStream::update_stream_hash() {
	m_td = mhash_init(MHASH_SHA1);
	if (td == MHASH_FAILED) return;
	else {
		for (Uint32 i=0; i<m_data.size(); i++)
			mhash(m_td, &m_data[i], 1);
		m_hash = mhash_end(m_td);
	}
}

std::string& TextStream::get_stream_hash() {
	return m_hash;
}