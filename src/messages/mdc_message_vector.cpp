/***************************************************************************
                          mdc_message_vector.cpp  -  Insert description
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
#include "mdc_message_vector.h"





vector<string> MDCMessageVector::get_rows() const
{
	return m_rows;
}




void MDCMessageVector::set_rows(const vector<string>& rows)
{
	m_rows = rows;
}




DataChunk& MDCMessageVector::serialize() const
{
	DataChunk* data = new DataChunk();
	
	(*data)+=MDCMessage::serialize();
	
	Uint32 num_rows = m_rows.size();
	
	data->append(num_rows);
	
	for(Uint32 i = 0; i<num_rows; i++)
	{
		data->append(m_rows[i].c_str());
	}
	
	
	return *data;
}





void MDCMessageVector::deserialize(const DataChunk& data)
{
	DataChunk temp_data;
	temp_data+=data;
	
	MDCMessage::deserialize(data);
	
	Uint8* mdc_header;
	
	temp_data.extract_head(8, mdc_header);
	
	if(temp_data.get_lenght()>0)
	{
		m_rows.empty();
		
		Uint32 num_rows;
		
		temp_data.extract_head(num_rows);
		
		m_rows.resize(num_rows);
		
		for(Uint32 i = 0; i<num_rows; i++)
		{
			char* temp_row;
			temp_data.extract_head(temp_row);
			m_rows[i] = temp_row;
		}
		
	}
	
}


Uint32 MDCMessageVector::get_num_rows() const
{
	return m_rows.size();
}

string MDCMessageVector::get_parameter_part(Uint32 index, string left_part) const
{
	string m_parameter = m_rows[index];
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


void MDCMessageVector::set_parameter_part(Uint32 index, string left_part, string right_part)
{
	string m_parameter =m_rows[index];
	string::size_type start_pos = m_parameter.find(left_part+"=", 0);
	if(start_pos != string::npos)
	{
		start_pos = start_pos + left_part.size() +1;
		string::size_type end_pos = m_parameter.find(';', start_pos);
		string::size_type substr_lenght = end_pos - start_pos;
		m_parameter.erase(start_pos, substr_lenght);
#ifdef USING_USTL
		m_parameter.insert(start_pos, right_part, right_part.size());
#else
		m_parameter.insert(start_pos, right_part);
#endif
	}
	else
	{
		m_parameter.append(left_part+"="+right_part+";");
	}
		
	
}



