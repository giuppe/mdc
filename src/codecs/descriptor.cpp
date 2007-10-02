/***************************************************************************
                          descriptor.cpp  -  MDC Descriptor class
                             -------------------
    begin                : Jul 13, 2007
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


#include "descriptor.h"



Uint8 Descriptor::get_flow_id() const
{
	return m_flow_id;
}




void Descriptor::set_flow_id(Uint8 id)
{
	m_flow_id= id;
}




Uint32 Descriptor::get_sequence_number() const
{
	return m_sequence_number;
}




void Descriptor::set_sequence_number(Uint32 seq_num)
{
	m_sequence_number = seq_num;
}




std::string Descriptor::get_file_name() const
{
	return m_file_name;
}




void Descriptor::set_file_name(const std::string& file_name)
{
	m_file_name = file_name;
}




std::string Descriptor::get_hash() const
{
	return m_hash;
}




void Descriptor::set_hash(const std::string& hash)
{
	m_hash = hash;
}




void Descriptor::set_codec_name(const std::string& codec_name)
{
	m_codec_name = codec_name;
}




std::string Descriptor::get_codec_name() const
{
	return m_codec_name;
}




AbstractCodecParameters* Descriptor::get_codec_parameter() const
{
	return codec_parameter;
}
