/***************************************************************************
                          md_stream.cpp  -  Insert description
                             -------------------
    begin                : July 13, 2007
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



#include "md_stream.h"
#include <vector>
#include <cassert>
#include "descriptor.h"


MDStream::MDStream():m_is_empty(true),m_is_inited(false)
{
	
}

MDStream::MDStream(Uint8 n_flows, Uint32 sequence_size):m_is_empty(true),m_is_inited(false)
{
	init(n_flows, sequence_size);
}

void MDStream::init(Uint8 n_flows, Uint32 sequence_size)
{
	m_stream.resize(n_flows);
	for(Uint32 i= 0; i<n_flows; i++)
	{
		m_stream[i].resize(sequence_size);
	}
	
	m_valid_descriptor.resize(n_flows);
	for(Uint8 i= 0; i<n_flows; i++)
	{
		m_valid_descriptor[i].resize(sequence_size, false);
	}
	
	m_is_inited = true;
	
}


bool MDStream::get_descriptor(Uint8 flow, Uint32 sequence, Descriptor* &descriptor) const
{
	if(m_valid_descriptor[flow][sequence]==true)
	{
		descriptor = m_stream[flow][sequence];
		return true;
	}
	return false;
}




void MDStream::set_descriptor(Descriptor* descriptor)
{
	m_is_empty = false;
	
	Uint8 flow = descriptor->get_flow_id();
	
	Uint32 sequence = descriptor->get_sequence_number();
	
	m_stream[flow][sequence] = descriptor;
	
	m_valid_descriptor[flow][sequence] = true;
	
	m_name = descriptor->get_file_name();
	
	m_hash = descriptor->get_hash();
	
}




std::string MDStream::get_name() const
{
	return m_name; 
}

std::string MDStream::get_hash() const
{
	return m_hash;
}





MDStream::~MDStream()
{
	if(m_is_inited == true)
	{
		if(m_is_empty == false)
		{
			for(Uint32 i = 0; i<m_valid_descriptor.size(); i++)
			{
				for(Uint32 k=0; k<m_valid_descriptor[i].size(); k++)
				{
					if(m_valid_descriptor[i][k]==true)
					{
						delete m_stream[i][k];
					}
				}
			}
		}
	}
}





bool MDStream::load_from_disk(const std::string& path)
{
	assert(!"this function is a stub and must be filled.");
	return false;
}
