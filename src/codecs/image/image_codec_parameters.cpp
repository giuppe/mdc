/***************************************************************************
           image_codec_parameters.cpp  -  Image Codec Parameters
                             -------------------
    begin                : Dec 13, 2007
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

#include "image_codec_parameters.h"
#include "../../common/data/mem_data_chunk.h"
#include "../../common/serializable.h"

ImageCodecParameters::ImageCodecParameters() {m_size = 5;}
Uint32 ImageCodecParameters::get_size() const {return m_size;}

MemDataChunk& ImageCodecParameters::serialize() const {
	MemDataChunk* dc = new MemDataChunk;
	dc->append_Uint16(m_width);
	dc->append_Uint16(m_height);
	dc->append_Uint8(m_bits_per_pixel);
	return *dc;
}

bool ImageCodecParameters::deserialize(const IDataChunk* dc) {

	DataChunkIterator it = dc->get_iterator();
	if(!it.get_Uint16(m_width))
	{
		return false;
	}
	if(!it.get_Uint16(m_height))
	{
		return false;
	}
	if(!it.get_Uint8(m_bits_per_pixel))
	{
		return false;
	}
	
	return true;
}

ImageCodecParameters::~ImageCodecParameters() {}
Uint16 ImageCodecParameters::get_width() {return m_width;}
void ImageCodecParameters::set_width(Uint16 width) {m_width = width;}
Uint16 ImageCodecParameters::get_height() {return m_height;}
void ImageCodecParameters::set_height(Uint16 height) {m_height = height;}
Uint8 ImageCodecParameters::get_bits_per_pixel() {return m_bits_per_pixel;}
void ImageCodecParameters::set_bits_per_pixel(Uint8 bits_number) {m_bits_per_pixel = bits_number;}
