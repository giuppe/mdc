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
#include "string.h"
#include "defs.h"
#include "vector.h"

bool TextStream::load_from_disk(const std::string& path) {
	FILE *m_f;
	char c;
	if (fopen(path.c_str(), "r") != NULL) {
		m_f = fopen(path.c_str(), "r");
		while (fscanf(m_f, "%c", &c) > 0) {
			characters.push_back(c);
		}
		fclose(m_f);
		return true;
	}
	else return false;
}

char TextStream::get_character(Uint32 position) const
{
	if (!characters.empty()) {
		if (position <= characters.size())
			return characters.at(position);
		else return NULL;
	}
	else return NULL;
}

Uint32 TextStream::get_characters_dim() const {
	return characters.size();
}

void TextStream::set_stream_name(std::string& name) {
	stream_name = name;
}

std::string& TextStream::get_stream_name() const {
	stream_name = path.substr(find_last_of(/), find_last_of(.)-1);
	return stream_name;
}

void TextStream::set_payload_size(Uint32 psize) const {
	size = psize;
}

Uint32 get_payload_size() {
	return size;
}