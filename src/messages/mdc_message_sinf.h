/***************************************************************************
                          mdc_message_sinf.h  -  Insert description
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

#ifndef MDC_MESSAGE_SINF_H_
#define MDC_MESSAGE_SINF_H_

class MDCMessageSinf : public MDCMessageSingleParameter
{

public:
	MDCMessageSinf()
	{
		
		this->init_header();

		this->set_type_string("SINF");
		
		m_parameter = "";

	}
	void set_stream_id(const std::string stream_id)
		{
			set_parameter_part(std::string("h"), stream_id);
		}
		
		std::string get_stream_id() const
		{
			
			return get_parameter_part(std::string("h"));
		}
	
};

#endif /*MDC_MESSAGE_SINF_H_*/
