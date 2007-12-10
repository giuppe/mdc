/***************************************************************************
                          mdc_message_vector.h  -  Insert description
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



#ifndef MDC_MESSAGE_VECTOR_H_
#define MDC_MESSAGE_VECTOR_H_




class MDCMessageVector : public MDCMessage
{
protected:
	
	vector<string> m_rows;
	
public:
	MDCMessageVector(){};
	
	DataChunk& serialize() const;
	
	void deserialize(const DataChunk&);
	

	

	

	
protected:
	
	Uint32 get_num_rows() const;
	
	vector<string> get_rows() const;
	
	void set_rows(const vector<string>& rows);
	
	string get_parameter_part(Uint32 index, string left_part) const;
		
	void set_parameter_part(Uint32 index, string left_part, string right_part);
	
};


#endif /*MDC_MESSAGE_VECTOR_H_*/
