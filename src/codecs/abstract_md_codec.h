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
public:
	
	/*
	 * Get flows number.
	 * @returns: flows number
	 */
	virtual Uint8 get_flows_number() = 0;
	
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
	virtual void set_flows_number (Uint8 number) = 0;
	
	/*
	 * Sets the payload size of descriptor.
	 * @size: desidered size of each descriptor
	 */
	virtual void set_payload_size (Uint16 size) = 0;
};

#endif /*ABSTRACTMDCODEC_H_*/
