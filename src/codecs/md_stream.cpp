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
#include "descriptor.h"



MDStream::MDStream(Uint8 n_flows, Uint32 sequence_size)
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
	Uint8 flow = descriptor->get_flow_id();
	
	Uint32 sequence = descriptor->get_sequence_number();
	
	m_stream[flow][sequence] = descriptor;
	
	m_valid_descriptor[flow][sequence] = true;
}

