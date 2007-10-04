/***************************************************************************
                          mdc_message.h  -  A message exchanged between MDC client and server 
                             -------------------
    begin                : Aug 17, 2007
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
#include "../common/serializable.h"

#ifndef MDC_MESSAGE_H_
#define MDC_MESSAGE_H_

class MDCMessage : public Serializable
{
	friend class Descriptor;
protected:
	Uint8* m_header_title;
	Uint8 m_version;
	Uint8* m_type;
	
	void set_type(Uint8* type);
	
	void set_type_string(const char* type);
	
public:
	
	MDCMessage();
	
	~MDCMessage();
	
	void init_header();
	

	
	Uint8* get_type() const;
	
	char* get_type_string() const;
	
	DataChunk& serialize() const;
	
	void deserialize(const DataChunk&);

};

#endif /*MDC_MESSAGE_H_*/
