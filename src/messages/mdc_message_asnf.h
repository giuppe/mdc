/***************************************************************************
                          mdc_message_asnf.h  -  Insert description
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
#include <string>

#ifndef MDC_MESSAGE_ASNF_H_
#define MDC_MESSAGE_ASNF_H_

class MDCMessageAsnf : public MDCMessageSingleParameter
{

public:
	MDCMessageAsnf()
	{
		
		this->init_header();

		this->set_type_string("ASNF");
		
		m_parameter = "";

	}
	
	void set_stream_id(const string stream_id)
	{
		set_parameter_part(string("h"), stream_id);
	}
	
	string get_stream_id() const
	{
		
		return get_parameter_part(string("h"));
	}
	
	void set_flows_number(const Uint8 flows_number)
	{
		char* buffer = new char[255];
		sprintf(buffer, "%d", flows_number);
		
			
		set_parameter_part(string("fn"), string(buffer));
		delete [] buffer;
	}
	
	Uint8 get_flows_number() const
	{
		
		return (Uint8) atoi(get_parameter_part(string("fn")).c_str());
	}
	
	void set_descriptors_number(const Uint32 descriptors_number)
	{
		char* buffer = new char[255];
		sprintf(buffer, "%d", descriptors_number);
		set_parameter_part(string("dn"), string(buffer));
		delete [] buffer;
	}
	
	Uint32 get_descriptors_number() const
	{
		
		return (Uint32) atoi(get_parameter_part(string("dn")).c_str());
	}
	

	
};

#endif /*MDC_MESSAGE_ASNF_H_*/
