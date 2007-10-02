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

	
};

#endif /*MDC_MESSAGE_ASNF_H_*/
