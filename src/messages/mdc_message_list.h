/***************************************************************************
                          mdc_message_list.h  -  Insert description
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

#ifndef MDC_MESSAGE_LIST_H_
#define MDC_MESSAGE_LIST_H_

class MDCMessageList : public MDCMessageSingleParameter
{

public:
	MDCMessageList()
	{
		
		this->init_header();

		this->set_type_string("LIST");
		
		m_parameter = "";

	}

	
};

#endif /*MDC_MESSAGE_LIST_H_*/
