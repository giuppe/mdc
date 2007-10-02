/***************************************************************************
                          codec_parameters.h  -  Codec Parameters abstract class
                             -------------------
    begin                : Jul 13 2007
    copyright          : (C) 2007 by Giuseppe D'Aqui', Livio Pipitone
    email                : kumber@tiscalinet.it
 ***************************************************************************/

/***************************************************************************
 *                                                                                                                 
 *   This program is free software; you can redistribute it and/or modify  
 *   it under the terms of the GNU General Public License, Version 2,        
 *   as published by the Free Software Foundation.                                  
 *                                                                                                                 
 ***************************************************************************/


#include "defs.h"
#include "../common/data_chunk.h"
#include "../common/serializable.h"

#ifndef ABSTRACT_CODEC_PARAMETERS_H_
#define ABSTRACT_CODEC_PARAMETERS_H_

class AbstractCodecParameters : public Serializable
{
protected:
	
	Uint32 m_size;
	
	
public:
	
	virtual DataChunk& serialize( ) = 0;
	
	virtual void deserialize(const DataChunk&)= 0;
	
	virtual ~AbstractCodecParameters(){};

};

#endif /*ABSTRACT_CODEC_PARAMETERS_H_*/
