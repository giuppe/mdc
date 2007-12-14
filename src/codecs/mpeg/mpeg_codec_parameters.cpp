/***************************************************************************
           mpeg_codec_parameters.cpp  -  MPEG Codec Parameters
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

#include "mpeg_codec_parameters.h"
#include "../../common/data/mem_data_chunk.h"
#include "../../common/serializable.h"

MpegCodecParameters::MpegCodecParameters() {m_size = 0;}

Uint32 MpegCodecParameters::get_size() const 
{
	return m_size;
}




MemDataChunk& MpegCodecParameters::serialize() const 
{
	MemDataChunk* dc = new MemDataChunk;
	return *dc;
}




void MpegCodecParameters::deserialize(const IDataChunk* dc) {}




MpegCodecParameters::~MpegCodecParameters() {}
