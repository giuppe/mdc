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
	m_flows_number = 2;
	m_preferred_payload_size = 19200; //pixel
	av_register_all( );
}

void VideoMDCodec::code(AbstractStream* stream, MDStream* md_stream) const {
	Uint32 frame_dimension = dynamic_cast<VideoStream*>(stream)->get_height()*dynamic_cast<VideoStream*>(stream)->get_width();//pixel
	Uint32 total_frame_number = dynamic_cast<VideoStream*>(stream)->get_last_frame_number()-1;
	//TODO è necessario reintrodurre il parametro max_payload_size dato che estraggo i pixel
	//e li inserisco in un frame per la codifica MPEG, oppure divido il frame originale per
	//il numero di flussi (rispettando sempre il rapporto base-altezza)?
	Uint32 descriptors_number = total_frame_number*(frame_dimension/m_preferred_payload_size);//for a single flow
	//md_stream->init(stream->compute_hash_md5(), m_flows_number, descriptors_number);
	//TODO preparare una struttura dati che contenga un singolo sotto-flusso che dovrà essere immediatamente codificato.
	//deve essere un Uint8* buffer...
	std::string filename = dynamic_cast<VideoStream*>(stream)->get_path().substr(dynamic_cast<VideoStream*>(stream)->get_path().find_last_of("/")+1, dynamic_cast<VideoStream*>(stream)->get_path().size());
	AVOutputFormat* fmt = guess_format(NULL, filename.c_str(), NULL);
	AVFormatContext* format_context = av_alloc_format_context();
	format_context->oformat = fmt;
	AVStream* video_stream = av_new_stream(format_context, 0);
	AVCodecContext* video_codec_context = video_stream->codec;
	video_codec_context->codec_id = fmt->video_codec;
	video_codec_context->codec_type = CODEC_TYPE_VIDEO;
	video_codec_context->bit_rate = dynamic_cast<VideoStream*>(stream)->get_bitrate();
	video_codec_context->time_base.den = 25;
	video_codec_context->time_base.num = 1;
	video_codec_context->gop_size = dynamic_cast<VideoStream*>(stream)->get_gop_size();
	video_codec_context->pix_fmt = PIX_FMT_YUV420P;
	Uint16 width = dynamic_cast<VideoStream*>(stream)->get_width();
	Uint16 height = dynamic_cast<VideoStream*>(stream)->get_height();
	video_codec_context->width = width;
	video_codec_context->height = height;
	av_set_parameters(format_context, NULL);
	AVCodec* video_codec = avcodec_find_encoder (video_codec_context->codec_id);
	avcodec_open(video_codec_context, video_codec);
	for (Uint32 l=0; l<total_frame_number; l++) {
		//Uint8* current_flow = new Uint8[400000];
		AVFrame* frame = avcodec_alloc_frame();
		Uint8* frame_buffer = new Uint8[avpicture_get_size(PIX_FMT_YUV420P, width, height)];
		MemDataChunk* stream_frame = &(stream->get_data(l*frame_dimension, frame_dimension));
		Uint8* current_frame = stream_frame->get_data();
		for (Uint8 i=0; i<m_flows_number; i++)
			extract_frame_description(stream, md_stream, stream_frame, descriptors_number, i, l, current_frame);
		delete stream_frame;
		//TODO la codifica deve essere effettuata sul frame appena estratto.
		avpicture_fill((AVPicture*)frame, frame_buffer, PIX_FMT_YUV420P, width, height);
		LOG_INFO("Frame "<<l<<" coded.");
		//TODO si deve codificare "in MPEG" il sotto-flusso restituito dalla funzione
		//alla fine devo mettere dentro l'md_stream N flussi, ognuno con un mega descrittore
		//e passarlo a video_stream.
	}
}

Uint8* VideoMDCodec::extract_frame_description(AbstractStream* stream, MDStream* md_stream, MemDataChunk* stream_frame, Uint32 descriptors_number, Uint8 i, Uint32 frame_number, Uint8* current_frame) const {
	Uint8* temp_frame = new Uint8[m_preferred_payload_size];
	Uint32 offset = 0;
	for (Uint8 j=0; j<descriptors_number; j++) {
		if (stream_frame->get_lenght()-(offset+i) > 0) {
			Descriptor* descriptor= new Descriptor();
			descriptor->set_stream_id(md_stream->get_stream_id());
			descriptor->set_flow_id(i);
			descriptor->set_sequence_number(j);
			descriptor->set_codec_name(string("video"));
			if (j == 0) {
				VideoCodecParameters* vcp = new VideoCodecParameters();
				vcp->set_frame_number(frame_number);
				vcp->set_width(dynamic_cast<VideoStream*>(stream)->get_width());
				vcp->set_height(dynamic_cast<VideoStream*>(stream)->get_height());
				vcp->set_bits_per_pixel(dynamic_cast<VideoStream*>(stream)->get_bits_per_pixel());
				MemDataChunk* temp_codec_parameters = &(vcp->serialize());
				descriptor->set_codec_parameter(vcp);
				delete temp_codec_parameters;
			}
			MemDataChunk payload;
			Uint16 k;
			for (k=0; k<m_preferred_payload_size; k++)
				if (offset+i+(k*m_flows_number) < stream_frame->get_lenght())
					payload.append_Uint8(current_frame[offset+i+(k*m_flows_number)]);
			offset += m_flows_number*k;
			descriptor->set_payload(payload);
			//TODO inserire i dati estratti in temp_frame e passarlo alla codifica MPEG
			md_stream->set_descriptor(descriptor);
		}
	}
}

void VideoMDCodec::decode(const MDStream* md_stream, AbstractStream* stream) const {
	if (!md_stream->is_empty()) {
		vector<pixel_container> took_stream;
		Uint8 flows_number = md_stream->get_flows_number();
		Uint32 sequences_number = md_stream->get_sequences_number();
		Uint16 frame_width, frame_height;
		Uint8 bpp = 0;
		bool null_pixel_present = false;
		for (Uint8 i=0; i<flows_number; i++) {
			Uint64 offset = 0;
			Uint16 payload_size = 0;
			for (Uint32 j=0; j<sequences_number; j++) {
				Descriptor* descriptor = new Descriptor();
				if (md_stream->get_descriptor(i, j, descriptor) && (descriptor->get_codec_name()=="image")) {
					payload_size = descriptor->get_payload_size();
					if (md_stream->is_valid(descriptor->get_flow_id(), descriptor->get_sequence_number())) {
						MemDataChunk* payload = descriptor->get_payload();
						took_stream.resize(flows_number*sequences_number*(payload_size+1));
						VideoCodecParameters* vcp = dynamic_cast<VideoCodecParameters*>(descriptor->get_codec_parameter());
						frame_width = vcp->get_width();
						frame_height = vcp->get_height();
						bpp = vcp->get_bits_per_pixel();
						if (bpp == 24) {
							Uint32 k;
							Uint32 pixels_in_payload = payload_size/3;
							DataChunkIterator it = payload->get_iterator();
							for (k=0; k<pixels_in_payload; k++) {
								pixel_container curr_pixel;
								Uint8 r,g,b;
								it.get_Uint8(r);
								it.get_Uint8(g);
								it.get_Uint8(b);
								curr_pixel.set_r(r);
								curr_pixel.set_g(g);
								curr_pixel.set_b(b);
								Uint32 locate_position = offset+i+(k*flows_number);
								took_stream[locate_position] = curr_pixel;
							}
							offset += flows_number*k;
						}
						delete payload;
					}
				}
				else {
					Uint32 k;
					Uint32 pixels_in_payload = payload_size/3;
					for (k=0; k<pixels_in_payload; k++) {
						Uint32 locate_position = offset+i+(k*flows_number);
						took_stream[locate_position] = m_null_pixel;
					}
					offset += flows_number*k;
					null_pixel_present = true;
				}
			}
		}
		Uint32 pixel_number = frame_width*frame_height;
		MemDataChunk* final_pixels= new MemDataChunk();
		final_pixels->resize(pixel_number*3);
		for (Uint32 i=0; i<pixel_number; i++) {
			MemDataChunk* pixel = &(took_stream[i].serialize());
			final_pixels->set_data_chunk(i*3, pixel);
			delete pixel;
		}
		dynamic_cast<VideoStream*>(stream)->set_width(frame_width);
		dynamic_cast<VideoStream*>(stream)->set_height(frame_height);
		dynamic_cast<VideoStream*>(stream)->set_bits_per_pixel(bpp);
		dynamic_cast<VideoStream*>(stream)->set_null_pixel_presence(null_pixel_present);
		stream->set_data(*final_pixels);
		delete final_pixels;
	}
}

VideoMDCodec::~VideoMDCodec() {}

void VideoMDCodec::set_flows_number (Uint8 number) {
	if ((number>0) && (number<65))
		m_flows_number = number;
	else {
		LOG_ERROR("Trying to set flows number to "<<number<<">64 (Max flows number for VideoMDCodec)");
	}
}

void VideoMDCodec::set_preferred_payload_size (Uint16 size) {
	if ((size>=10) && (size<=18330))
		m_preferred_payload_size = size;
	else {
		LOG_ERROR("Trying to set preferred payload to "<<size<<": for VideoMDCodec should be in range [10,18330]");
	}
}

void VideoMDCodec::set_null_pixel_colors(Uint8 r, Uint8 g, Uint8 b) {
	m_null_pixel.set_r(r);
	m_null_pixel.set_g(g);
	m_null_pixel.set_b(b);
}

pixel_container VideoMDCodec::get_null_pixel_colors() {return m_null_pixel;}
