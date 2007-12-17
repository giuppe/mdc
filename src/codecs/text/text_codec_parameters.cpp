/***************************************************************************
           text_codec_parameters.cpp  -  Text Codec Parameters
                             -------------------
    begin                : Oct 14 2007
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

#include "text_codec_parameters.h"
#include "../../common/data/mem_data_chunk.h"
#include "../../common/serializable.h"

TextCodecParameters::TextCodecParameters() {m_size = 0;}

Uint32 TextCodecParameters::get_size() const 
{
	return m_size;
}




MemDataChunk& TextCodecParameters::serialize() const 
{
	MemDataChunk* dc = new MemDataChunk;
	return *dc;
}




bool TextCodecParameters::deserialize(const IDataChunk* dc) {return true;}




TextCodecParameters::~TextCodecParameters() {}
