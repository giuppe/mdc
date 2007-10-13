/***************************************************************************
                          AbstractMDCodec.h  -  MD codec abstract class
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
	virtual void set_flows_number (Uint8 flows) = 0;
	virtual Uint8 get_flows_number () = 0;
	virtual void code(const AbstractStream* stream, MDStream* md_stream) = 0;
	virtual void decode(const MDStream* md_stream, AbstractStream* stream) = 0;
	virtual ~AbstractMDCodec(){};
};

#endif /*ABSTRACTMDCODEC_H_*/
