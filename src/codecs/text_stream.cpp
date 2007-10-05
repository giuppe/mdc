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

bool TextStream::load_from_disk(const std::string& path) {
	FILE *m_f;
	char* c;
	if (fopen(path.c_str(), "r") != NULL) {
		m_f = fopen(path.c_str(), "r");
		while (fscanf(m_f, "%c", c) > 0) {
			character = c;
		}
		fclose(m_f);
		return true;
	}
	else return false;
}

char& TextStream::get_character() {
	return character;
}