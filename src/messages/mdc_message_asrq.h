/***************************************************************************
                          mdc_message_asrq.h  -  Insert description
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

#ifndef MDC_MESSAGE_ASRQ_H_
#define MDC_MESSAGE_ASRQ_H_

class MDCMessageAsrq : public MDCMessageSingleParameter
{

public:
	MDCMessageAsrq()
	{
		
		this->init_header();

		this->set_type_string("ASRQ");
		
		m_parameter = "";

	}
	
	
	void set_hash(std::string hash);
	
	std::string get_hash() const;
	
	void set_flow_id(Uint8 flow_id);
	
	Uint8 get_flow_id() const;
	
	void set_sequence_begin(Uint32 sequence_begin);
	
	void set_sequence_end(Uint32 sequence_end);
	
	Uint32 get_sequence_begin() const;

	Uint32 get_sequence_end() const;

	
};

#endif /*MDC_MESSAGE_ASRQ_H_*/
