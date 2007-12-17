/***************************************************************************
           text_codec_parameters.h  -  Text Codec Parameters class
                             -------------------
    begin                : Oct 4 2007
    copyright            : Livio Pipitone
    email                : livent@tiscalinet.it
 ***************************************************************************/

/***************************************************************************
 *                                                                                                                 
 *   This program is free software; you can redistribute it and/or modify  
 *   it under the terms of the GNU General Public License, Version 2,        
 *   as published by the Free Software Foundation.                                  
 *                                                                                                                 
 ***************************************************************************/

#include "defs.h"
#include "../../common/data/mem_data_chunk.h"
#include "../../common/serializable.h"
#include "../abstract_codec_parameters.h"

#ifndef TEXT_CODEC_PARAMETERS_H_
#define TEXT_CODEC_PARAMETERS_H_

class TextCodecParameters : public AbstractCodecParameters
{
public:

	/*
	 * Initialize text codec parameters.
	 */
	TextCodecParameters();

	/*
	 * Serialize a data chunk.
	 * @returns: data chunk
	 */
	MemDataChunk& serialize() const;

	/*
	 * Deserialize a data chunk.
	 */
	bool deserialize(const IDataChunk* dc);
	
	/*
	 * Get parameters' size.
	 * @returns: parameters' size
	 */
	Uint32 get_size() const;
	
	
	~TextCodecParameters();
};

#endif /*TEXT_CODEC_PARAMETERS_H_*/
