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
#include "pcx_stream.h"



#ifndef PCX_CODEC_PARAMETERS_H_
#define PCX_CODEC_PARAMETERS_H_

class PcxCodecParameters : public AbstractCodecParameters
{
protected:
	Uint8 m_headerinfo[128];
	Uint8 m_bytes_per_line;
	DataChunk sdata;
public:

	/*
	 * Initialize text codec parameters.
	 */
	PcxCodecParameters();

	void extractPcxCodecParameters(AbstractStream* stream);
	
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
	Uint32 get_size() const;
	
	/*
	 * Get parameters' bytes_per_line.
	 * @returns: parameters' bytes_per_line
	 */
	Uint8 get_bytes_per_line() const;
	
	~PcxCodecParameters();
};


#endif /*PCX_CODEC_PARAMETERS_H_*/
