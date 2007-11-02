/***************************************************************************
           pcx_codec_parameters.h  -  PCX Codec Parameters class
                             -------------------
    begin                : Oct 31 2007
    copyright            : Ivan Coppa
    email                : ivan.coppa@gmail.com
 ***************************************************************************/

/***************************************************************************
 *                                                                                                                 
 *   This program is free software; you can redistribute it and/or modify  
 *   it under the terms of the GNU General Public License, Version 2,        
 *   as published by the Free Software Foundation.                                  
 *                                                                                                                 
 ***************************************************************************/

#include "defs.h"
#include "../../common/data_chunk.h"
#include "../../common/serializable.h"
#include "../abstract_codec_parameters.h"

#ifndef PCX_CODEC_PARAMETER_
#define PCX_CODEC_PARAMETER_



class PcxCodecParameters : public AbstractCodecParameters
{
public:

	/*
	 * Initialize text codec parameters.
	 */
	PcxCodecParameters();

	/*
	 * Serialize a data chunk.
	 * @returns: data chunk
	 */
	DataChunk& serialize() const;

	/*
	 * Deserialize a data chunk.
	 */
	void deserialize(const DataChunk& dc);
	
	/*
	 * Get parameters' size.
	 * @returns: parameters' size
	 */
	Uint32 get_size();
	~PcxCodecParameters();
};

#endif /*PCX_CODEC_PARAMETER_*/