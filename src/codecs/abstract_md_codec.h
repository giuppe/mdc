/***************************************************************************
                abstract_md_codec.h  -  MD codec abstract class
                             -------------------
    begin                : Jul 13, 2007
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

#include "md_stream.h"
#include "abstract_stream.h"

#ifndef ABSTRACTMDCODEC_H_
#define ABSTRACTMDCODEC_H_

class AbstractMDCodec
{
protected:
	Uint8 m_flows_number;
	Uint16 m_preferred_payload_size;
public:
	
	/*
	 * Get flows number.
	 * @returns: flows number
	 */
	Uint8 get_flows_number(){return m_flows_number;};
	
	/*
	 * Code an abstract stream in an abstract md_stream
	 * @stream: abstract description of a generic stream
	 * @md_stream: abstract description of a generic stream coded by MDC
	 */
	virtual void code(AbstractStream* stream, MDStream* md_stream) = 0;
	
	/*
	 * Decode an abstract md_stream and fills up an abstract stream
	 * @stream: abstract description of a generic stream
	 * @md_stream: abstract description of a generic stream coded by MDC
	 */
	virtual void decode(const MDStream* md_stream, AbstractStream* stream) = 0;
	virtual ~AbstractMDCodec(){};
	
	/*
	 * Sets the flows number.
	 * @number: flows number into which the generic stream must to be divided before coding
	 * process
	 */
	void set_flows_number (Uint8 number){m_flows_number = number;};
	
	/*
	 * Sets the payload size of descriptor.
	 * @size: desidered size of each descriptor
	 */
	void set_preferred_payload_size (Uint16 size){m_preferred_payload_size = size;};
};

#endif /*ABSTRACTMDCODEC_H_*/
