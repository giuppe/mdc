/***************************************************************************
                          mdc_message_alst.h  -  Insert description
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
#include <string>
#include <vector>
#include <cassert>

#ifndef MDC_MESSAGE_ALST_H_
#define MDC_MESSAGE_ALST_H_

class MDCMessageAlst : public MDCMessageVector
{
	
public:
	
	MDCMessageAlst()
	{
		this->init_header();

		this->set_type_string("ALST");
		
		

	}
	
	void append_entry(std::string name, std::string hash)
	{
		std::string entry = "n=";
		entry += name;
		entry += "&";
		entry += "h=";
		entry += hash;
		m_rows.push_back(entry);
	}
	
	std::string get_entry_name(Uint32 num_entry) const
	{
		if(num_entry>m_rows.size())
		{
			LOG_ERROR("Trying to get a parameter outside range.")
			return "";
		}
		
		std::string entry = m_rows[num_entry];
		
		assert(!"This function is a stub.");
		return "";
	}
	
	std::string get_entry_hash(Uint32 num_entry) const
	{
			
			assert(!"This function is a stub.");
			return "";
	}
	
};

#endif /*MDC_MESSAGE_ALST_H_*/
