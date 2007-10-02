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
	
	
};

#endif /*MDC_MESSAGE_ALST_H_*/
