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

std::string MDCMessageSingleParameter::get_parameter_part(std::string left_part) const
{
	
	std::string::size_type start_pos = m_parameter.find(left_part+"=", 0);
	if(start_pos != std::string::npos)
	{
		start_pos = start_pos + left_part.size() +1;
		std::string::size_type end_pos = m_parameter.find(';', start_pos);
		std::string::size_type substr_lenght = end_pos - start_pos;
		return m_parameter.substr(start_pos, substr_lenght);
	}
	return "";
}


void MDCMessageSingleParameter::set_parameter_part(std::string left_part, std::string right_part)
{
	std::string::size_type start_pos = m_parameter.find(left_part+"=", 0);
	if(start_pos != std::string::npos)
	{
		start_pos = start_pos + left_part.size() +1;
		std::string::size_type end_pos = m_parameter.find(';', start_pos);
		std::string::size_type substr_lenght = end_pos - start_pos;
		m_parameter.erase(start_pos, substr_lenght);
		m_parameter.insert(start_pos, right_part);
	}
	else
	{
		m_parameter.append(left_part+"="+right_part+";");
	}
		
	
}
