/***************************************************************************
           video_codec_parameters.cpp  -  Video Codec Parameters
                             -------------------
    begin                : May 7, 2008
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

#include "video_codec_parameters.h"
#include "../../common/data/mem_data_chunk.h"
#include "../../common/serializable.h"

VideoCodecParameters::VideoCodecParameters() {m_size = 9;}
Uint32 VideoCodecParameters::get_size() const {return m_size;}

MemDataChunk& VideoCodecParameters::serialize() const {
	MemDataChunk* dc = new MemDataChunk;
	dc->append_Uint32(m_frame_number);
	dc->append_Uint16(m_width);
	dc->append_Uint16(m_height);
	dc->append_Uint8(m_bits_per_pixel);
	return *dc;
}

bool VideoCodecParameters::deserialize(const IDataChunk* dc) {
	DataChunkIterator it = dc->get_iterator();
	if(!it.get_Uint32(m_frame_number)) return false;
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

VideoCodecParameters::~VideoCodecParameters() {}
Uint16 VideoCodecParameters::get_width() {return m_width;}
void VideoCodecParameters::set_width(Uint16 width) {m_width = width;}
Uint16 VideoCodecParameters::get_height() {return m_height;}
void VideoCodecParameters::set_height(Uint16 height) {m_height = height;}
Uint8 VideoCodecParameters::get_bits_per_pixel() {return m_bits_per_pixel;}
void VideoCodecParameters::set_bits_per_pixel(Uint8 bits_number) {m_bits_per_pixel = bits_number;}
void VideoCodecParameters::set_frame_number(Uint32 number) {m_frame_number = number;}
Uint32 VideoCodecParameters::get_frame_number() {return m_frame_number;}