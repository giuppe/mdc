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
#include "../common/data/mem_data_chunk.h"
#include "../common/serializable.h"

#ifndef ABSTRACT_CODEC_PARAMETERS_H_
#define ABSTRACT_CODEC_PARAMETERS_H_

/**
 * This abstract class represents generic codec parameters.
 * Codec parameters are informations about coding, such as 
 * color bit depth in an image, sampling/quantization parameters etc.
 * You must derive this class for each codec you create.  
*/
class AbstractCodecParameters : public Serializable
{
protected:
	Uint32 m_size;
public:
	
	/*
	 * Serialize a data chunk.
	 */
	virtual MemDataChunk& serialize() const = 0;
	
	/*
	 * Deserialize a data chunk.
	 */
	virtual bool deserialize(const IDataChunk*) = 0;
	
	/*
	 * Returns parameters' size.
	 */
	virtual Uint32 get_size() const = 0;
	
	virtual ~AbstractCodecParameters(){};

};

#endif /*ABSTRACT_CODEC_PARAMETERS_H_*/
