/***************************************************************************
                          mdc_message.cpp  -  Insert description
                             -------------------
    begin                : Sep 12, 2007
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

#include "defs.h"
#include "mdc_message.h"

MDCMessage::MDCMessage()
{
	init_header();
}
	
void MDCMessage::init_header()
{
	m_header_title = new Uint8[3];
	memcpy(this->m_header_title, "MDC", 3);
	m_version = 0;
	m_type = new Uint8[4];
}
	
void MDCMessage::set_type(Uint8* type)
{

	memcpy(m_type, type, 4);
}
	
Uint8* MDCMessage::get_type() const
{
	return m_type;
}




char* MDCMessage::get_type_string() const 
{
	char* type = new char[5];
	memset(type, 0, 5);
	memcpy(type, m_type, 4);
	
	return type;
}

void MDCMessage::set_type_string(const char* type) {
	Uint8* byte_type = new Uint8[4];
	memcpy(byte_type, type, 4);
	set_type(byte_type);
}

DataChunk& MDCMessage::serialize() const
{
	DataChunk* data = new DataChunk();
	data->append((Uint32) 3, m_header_title);
	data->append(m_version);
	data->append((Uint32) 4, m_type);
	return *data;
}
	
void MDCMessage::deserialize(const DataChunk& data)
{
	DataChunk temp_data;
	temp_data+=data;
	temp_data.extract_head(3, m_header_title);
	temp_data.extract_head(m_version);
	temp_data.extract_head(4, m_type);
	
}

MDCMessage::~MDCMessage()
{
	delete [] m_header_title;
	delete [] m_type;
}

