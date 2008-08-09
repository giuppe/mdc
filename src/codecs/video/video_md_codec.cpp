/***************************************************************************
                  video_md_codec.cpp  -  Management class for video codec
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

#include "video_md_codec.h"
#include "defs.h"
#include "video_stream.h"
#include "../mdc/md_stream.h"
#include "../mdc/descriptor.h"
#include "../../common/data/mem_data_chunk.h"
#include "video_codec_parameters.h"
#include <ffmpeg/avformat.h>
#include <ffmpeg/avcodec.h>

VideoMDCodec::VideoMDCodec() {
	m_flows_number = 4;
	av_register_all( );
}

void VideoMDCodec::code(AbstractStream* stream, MDStream* md_stream) const {
	if ((dynamic_cast<VideoStream*>(stream)->get_width()%m_flows_number!=0) && (dynamic_cast<VideoStream*>(stream)->get_height()%m_flows_number!=0)) {
		LOG_ERROR("Cannot convert this file: width and height must to be divisible by "<<m_flows_number<<".");
		return;
	}
	Uint32 frame_dimension = dynamic_cast<VideoStream*>(stream)->get_height()*dynamic_cast<VideoStream*>(stream)->get_width();//pixel
	Uint32 total_frame_number = dynamic_cast<VideoStream*>(stream)->get_last_frame_number()-1;
	Uint8* description_1 = new Uint8[frame_dimension*3*total_frame_number];
	Uint8* description_2 = new Uint8[frame_dimension*3*total_frame_number];
	Uint8* description_3 = new Uint8[frame_dimension*3*total_frame_number];
	Uint8* description_4 = new Uint8[frame_dimension*3*total_frame_number];
	for (Uint32 l=0; l<1; l++) { //must be total_frame_number
		MemDataChunk* mem = new MemDataChunk();
		*mem = stream->get_data(l*frame_dimension, frame_dimension);
		for (Uint8 i=0; i<m_flows_number; i++) {
			Uint8* current_descriptor = extract_frame_descriptor(mem, i, frame_dimension);
			switch (i) {
			case 0:
				for (Uint32 j=0; j<frame_dimension*3; j++)
					description_1[j+(l*frame_dimension)] = current_descriptor[j];
				break;
			case 1:
				for (Uint32 j=0; j<frame_dimension*3; j++)
					description_2[j+(l*frame_dimension)] = current_descriptor[j];
				break;
			case 2:
				for (Uint32 j=0; j<frame_dimension*3; j++)
					description_3[j+(l*frame_dimension)] = current_descriptor[j];
				break;
			case 3:
				for (Uint32 j=0; j<frame_dimension*3; j++)
					description_4[j+(l*frame_dimension)] = current_descriptor[j];
				break;
			}
		}
		LOG_INFO("Frame "<<l+1<<" coded.");
	}
	dynamic_cast<VideoStream*>(stream)->save_video_stream(description_1, "1", m_flows_number);
	dynamic_cast<VideoStream*>(stream)->save_video_stream(description_2, "2", m_flows_number);
	dynamic_cast<VideoStream*>(stream)->save_video_stream(description_3, "3", m_flows_number);
	dynamic_cast<VideoStream*>(stream)->save_video_stream(description_4, "4", m_flows_number);
}

Uint8* VideoMDCodec::extract_frame_descriptor(MemDataChunk* stream_frame, Uint8 i, Uint32 frame_dimension) const {
	Uint8* current_frame = stream_frame->get_data();
	Uint8* current_descriptor = new Uint8[stream_frame->get_lenght()];
	for (Uint32 k=0; k<frame_dimension/m_flows_number; k++) {
		Uint32 current_position = i+(k*m_flows_number*3);
		for (Uint32 m=current_position; m<(m_flows_number*3)+current_position; m+=3) {
			current_descriptor[m] = current_frame[current_position];
			current_descriptor[1+m] = current_frame[current_position+1];
			current_descriptor[2+m] = current_frame[current_position+2];
		}
	}
	return current_descriptor;
}

void VideoMDCodec::decode(const MDStream* md_stream, AbstractStream* stream) const {}
VideoMDCodec::~VideoMDCodec() {}

void VideoMDCodec::set_flows_number (Uint8 number) {
	if ((number>0) && (number<65))
		m_flows_number = number;
	else {
		LOG_ERROR("Trying to set flows number to "<<number<<">64 (Max flows number for VideoMDCodec)");
	}
}

void VideoMDCodec::set_preferred_payload_size (Uint16 size) {}
void VideoMDCodec::set_null_pixel_colors(Uint8 r, Uint8 g, Uint8 b) {}
pixel_container VideoMDCodec::get_null_pixel_colors() {}
