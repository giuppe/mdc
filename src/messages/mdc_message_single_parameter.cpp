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

MemDataChunk& MDCMessageSingleParameter::serialize() const
{
	MemDataChunk* data = new MemDataChunk();
	
	(*data)+=&MDCMessage::serialize();
	
	data->append_cstring(m_parameter.c_str());
	
	return *data;
}
	
bool MDCMessageSingleParameter::deserialize(const IDataChunk* data)
{
	DataChunkIterator it;
	if(data->get_lenght()==0)
		return false;
	
	it = data->get_iterator();
	
	IDataChunk* mdc_header;
	
	it.get_data_chunk(8, mdc_header);
		
	
	if(!MDCMessage::deserialize(mdc_header))
	{
		return false;
	}
	
	
	if(it.has_next())
	{
		char* parameter;
		it.get_cstring(parameter);
		m_parameter = parameter;
		return true;
	}
	return false;
}

string MDCMessageSingleParameter::get_parameter_part(string left_part) const
{
	
	string::size_type start_pos = m_parameter.find(left_part+"=", 0);
	if(start_pos != string::npos)
	{
		start_pos = start_pos + left_part.size() +1;
		string::size_type end_pos = m_parameter.find(';', start_pos);
		string::size_type substr_lenght = end_pos - start_pos;
		return m_parameter.substr(start_pos, substr_lenght);
	}
	return "";
}


void MDCMessageSingleParameter::set_parameter_part(string param_key, string param_value)
{
	string::size_type old_param_value_start_pos = m_parameter.find(param_key+"=", 0);
	if(old_param_value_start_pos != string::npos)
	{
		old_param_value_start_pos = old_param_value_start_pos + param_key.size() +1;
		string::size_type old_param_value_end_pos = m_parameter.find(';', old_param_value_start_pos);
		string::size_type old_param_value_lenght = old_param_value_end_pos - old_param_value_start_pos;
		m_parameter.erase(old_param_value_start_pos, old_param_value_lenght);
#ifdef USING_USTL
		m_parameter.insert(old_param_value_start_pos, param_value, param_value.size());
#else
		m_parameter.insert(old_param_value_start_pos, param_value);
#endif
	}
	else
	{
		m_parameter.append(param_key+"="+param_value+";");
	}
		
	
}
