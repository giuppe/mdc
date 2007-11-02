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

#include "pcx_codec_parameters.h"
//#include "../../common/data_chunk.h"
//#include "../../common/serializable.h"

PcxCodecParameters::PcxCodecParameters() {m_size = 0;}

Uint32 PcxCodecParameters::get_size() {return m_size;}

DataChunk& PcxCodecParameters::serialize() const {
	DataChunk* dc = new DataChunk;
	return *dc;
}

void PcxCodecParameters::deserialize(const DataChunk& dc) {}

PcxCodecParameters::~PcxCodecParameters() {}
