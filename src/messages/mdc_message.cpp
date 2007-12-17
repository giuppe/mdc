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

MemDataChunk& MDCMessage::serialize() const
{
	MemDataChunk* data = new MemDataChunk();
	data->append_data((Uint32) 3, m_header_title);
	data->append_Uint8(m_version);
	data->append_data((Uint32) 4, m_type);
	return *data;
}
	
bool MDCMessage::deserialize(const IDataChunk* data)
{
	DataChunkIterator it;
	if(data->get_lenght()==0)
		return false;
	
	it = data->get_iterator();
	
	if(!(it.get_data(3, m_header_title)))
	{
		return false;
	}
	
	if(!it.get_Uint8(m_version))
	{
		return false;
	}
	
	if(!it.get_data(4, m_type))
	{
		return false;
	}
	
	return true;
	
}

MDCMessage::~MDCMessage()
{
	delete [] m_header_title;
	delete [] m_type;
}

