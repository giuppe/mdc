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
	 * Set flows number.
	 * @flows: flows number
	 */
	virtual void set_flows_number(Uint8 flows) = 0;
	
	/*
	 * Get flows number.
	 * @returns: flows number
	 */
	virtual Uint8 get_flows_number() = 0;
	
	/*
	 * Set descriptors dimension by GUI.
	 * @dimension: descriptors payload dimension and header
	 */
	virtual void set_descriptor_dimension(Uint16 total_dimension) = 0;
	
	/*
	 * Code an abstract stream in an abstract md_stream
	 * @stream: abstract description of a generic stream
	 * @md_stream: abstract description of a generic stream coded by MDC
	 */
	virtual void code(AbstractStream* stream, MDStream* md_stream) = 0;
	virtual void decode(const MDStream* md_stream, AbstractStream* stream) = 0;
	virtual ~AbstractMDCodec(){};
};

#endif /*ABSTRACTMDCODEC_H_*/
