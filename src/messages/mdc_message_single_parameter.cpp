/***************************************************************************
                          mdc_message_single_parameter.cpp  -  Insert description
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
#include "mdc_message_single_parameter.h"


const char* MDCMessageSingleParameter::get_parameter() const
{
	return m_parameter.c_str();
}

void MDCMessageSingleParameter::set_parameter(const char* parameter)
{
	m_parameter = parameter;
}

DataChunk& MDCMessageSingleParameter::serialize() const
{
	DataChunk* data = new DataChunk();
	
	(*data)+=MDCMessage::serialize();
	
	data->append(m_parameter.c_str());
	
	return *data;
}
	
void MDCMessageSingleParameter::deserialize(const DataChunk& data)
{
	DataChunk temp_data;
	temp_data+=data;
	
	MDCMessage::deserialize(data);
	
	Uint8* mdc_header;
	
	temp_data.extract_head(8, mdc_header);
	
	if(temp_data.get_lenght()>0)
	{
		char* parameter;
		temp_data.extract_head(parameter);
		m_parameter = parameter;
	}
	
}
