/***************************************************************************
                 pixel_container.cpp  -  Insert color information
                             -------------------
    begin                : Dec 13, 2007
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

#include "pixel_container.h"

pixel_container::pixel_container() {
	m_r = 0;
	m_g = 0;
	m_b = 0;
}

pixel_container::~pixel_container() {}
void pixel_container::set_r(Uint8 red) {m_r = red;}
void pixel_container::set_g(Uint8 green) {m_g = green;}
void pixel_container::set_b(Uint8 blue) {m_b = blue;}
Uint8 pixel_container::get_r() const {return m_r;}
Uint8 pixel_container::get_g() const {return m_g;}
Uint8 pixel_container::get_b() const {return m_b;}

MemDataChunk& pixel_container::serialize() const {
	MemDataChunk* d = new MemDataChunk();
	d->append_Uint8(m_r);
	d->append_Uint8(m_g);
	d->append_Uint8(m_b);
	return *d;
}

bool pixel_container::deserialize(const IDataChunk* data) {
	MemDataChunk temp_data;
	temp_data += data;
	temp_data.extract_head(m_r);
	temp_data.extract_head(m_g);
	temp_data.extract_head(m_b);
}
