/***************************************************************************
           mpeg_codec_parameters.h  -  MPEG Codec Parameters class
                             -------------------
    begin                : Dec 7, 2007
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

#ifndef MPEG_CODEC_PARAMETERS_H_
#define MPEG_CODEC_PARAMETERS_H_

class MpegCodecParameters : public AbstractCodecParameters {
public:

	/*
	 * Initialize mpeg codec parameters.
	 */
	MpegCodecParameters();

	/*
	 * Serialize a data chunk.
	 * @returns: data chunk
	 */
	MemDataChunk& serialize() const;

	/*
	 * Deserialize a data chunk.
	 */
	void deserialize(const IDataChunk* dc);
	
	/*
	 * Get parameters' size.
	 * @returns: parameters' size
	 */
	Uint32 get_size() const;
	
	
	~MpegCodecParameters();
};

#endif /*MPEG_CODEC_PARAMETERS_H_*/
