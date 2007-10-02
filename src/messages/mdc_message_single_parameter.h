/***************************************************************************
                          mdc_message_parm.h  -  Insert description
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
#include "mdc_message.h"
#include <string>

#ifndef MDC_MESSAGE_SINGLE_PARAMETER_H_
#define MDC_MESSAGE_SINGLE_PARAMETER_H_

class MDCMessageSingleParameter : public MDCMessage
{
protected:
	std::string m_parameter;
public:
	MDCMessageSingleParameter(){};
	
	DataChunk& serialize() const;
	
	void deserialize(const DataChunk&);
	
	const char* get_parameter() const;
	
	void set_parameter(const char* parameter);
	
};

#endif /*MDC_MESSAGE_SINGLE_PARAMETER_H_*/
