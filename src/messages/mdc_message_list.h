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
	
	void set_name(const std::string name)
	{
		m_parameter = "n=";
		m_parameter+= name;
		m_parameter+= ";";
	}
	
	std::string get_name() const
	{
		std::string result =  m_parameter.substr(2, m_parameter.find_first_of(';',2));
		
		return result;
	}

	
};

#endif /*MDC_MESSAGE_LIST_H_*/
