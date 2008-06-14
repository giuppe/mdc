/***************************************************************************
                  image_md_codec.cpp  -  Management class for image codec
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

#include "image_md_codec.h"
#include "defs.h"
#include "image_stream.h"
#include "../mdc/md_stream.h"
#include "../mdc/descriptor.h"
#include "../../common/data/mem_data_chunk.h"
#include "image_codec_parameters.h"
#include <cmath>
#include "/usr/include/lzo/lzo1x.h"

ImageMDCodec::ImageMDCodec() {
	m_seq_counter.push_back(0);
	m_flows_number = 2;
	m_preferred_payload_size = 1000; //pixel
}

void ImageMDCodec::code(AbstractStream* stream, MDStream* md_stream) const {
	Uint32 stream_size = stream->get_data_dim();
	Uint32 flow_dimension = (stream_size/m_flows_number)+1;
	Uint32 descriptors_number = (Uint32)ceil(((double)flow_dimension)/((double)m_preferred_payload_size));
	Uint16 max_payload_size = (flow_dimension/descriptors_number)+1;
	md_stream->init(stream->compute_hash_md5(), m_flows_number, descriptors_number);
	for (Uint8 i=0; i<m_flows_number; i++) {
		Uint64 offset = 0;
		for (Uint32 j=0; j<descriptors_number; j++) {
			if (stream_size-(offset+i) > 0) {
				Descriptor* descriptor= new Descriptor();
				descriptor->set_stream_id(md_stream->get_stream_id());
				descriptor->set_flow_id(i);
				descriptor->set_sequence_number(j);
				descriptor->set_codec_name(string("image"));
				ImageCodecParameters* icp = new ImageCodecParameters();
				icp->set_width(dynamic_cast<ImageStream*>(stream)->get_width());
				icp->set_height(dynamic_cast<ImageStream*>(stream)->get_height());
				icp->set_bits_per_pixel(dynamic_cast<ImageStream*>(stream)->get_bits_per_pixel());
				MemDataChunk* temp_codec_parameters = &(icp->serialize());
				descriptor->set_codec_parameter(icp);
				delete temp_codec_parameters;
				MemDataChunk payload;
				Uint16 k;
				for (k=0; k<max_payload_size; k++)
					if (offset+i+(k*m_flows_number) < stream_size) {
						MemDataChunk* stream_data = &(stream->get_data(offset+i+(k*m_flows_number), 1)); 
						payload += stream_data;
						delete stream_data;
					}
				offset += m_flows_number*k;
				MemDataChunk compressed_payload;
				compressed_payload.append_data(payload.get_compressed_size(), payload.get_compressed_data());
				descriptor->set_payload(compressed_payload);
				md_stream->set_descriptor(descriptor);
			}
		}
	}
}

void ImageMDCodec::decode(const MDStream* md_stream, AbstractStream* stream) const {
	if (!md_stream->is_empty()) {
		vector<pixel_container> took_stream;
		Uint8 flows_number = md_stream->get_flows_number();
		Uint32 sequences_number = md_stream->get_sequences_number();
		Uint16 image_width, image_height;
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
						MemDataChunk* payload = decompression(descriptor->get_payload(), payload_size);
						payload_size = payload->get_lenght();
						took_stream.resize(flows_number*sequences_number*(payload_size+1));
						ImageCodecParameters* icp = dynamic_cast<ImageCodecParameters*>(descriptor->get_codec_parameter());
						image_width = icp->get_width();
						image_height = icp->get_height();
						bpp = icp->get_bits_per_pixel();
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

		Uint32 pixel_number = image_width*image_height;
		MemDataChunk* final_pixels= new MemDataChunk();
		final_pixels->resize(pixel_number*3);
		for (Uint32 i=0; i<pixel_number; i++) {
			MemDataChunk* pixel = &(took_stream[i].serialize());
			final_pixels->set_data_chunk(i*3, pixel);
			delete pixel;
		}
		dynamic_cast<ImageStream*>(stream)->set_width(image_width);
		dynamic_cast<ImageStream*>(stream)->set_height(image_height);
		dynamic_cast<ImageStream*>(stream)->set_bits_per_pixel(bpp);
		dynamic_cast<ImageStream*>(stream)->set_null_pixel_presence(null_pixel_present);
		stream->set_data(*final_pixels);
		delete final_pixels;
	}
}

MemDataChunk* ImageMDCodec::decompression(MemDataChunk* compressed_payload, Uint16 payload_size) const {
	if (lzo_init() != LZO_E_OK) {
		LOG_ERROR("LZO initialization failed for decompression procedure!\n");
		return 0;
	}
	lzo_uint data_size;
	Uint8* output_data = new Uint8[65535];
	lzo1x_decompress(compressed_payload->get_data(), payload_size, output_data, &data_size, NULL);
	MemDataChunk* decompressed_payload = new MemDataChunk();
	decompressed_payload->append_data((Uint32)data_size, output_data);
	delete [] output_data;
	return decompressed_payload;
}

ImageMDCodec::~ImageMDCodec() {}

void ImageMDCodec::set_flows_number (Uint8 number) {
	if ((number>0) && (number<65))
		m_flows_number = number;
	else {
		LOG_ERROR("Trying to set flows number to "<<number<<">64 (Max flows number for ImageMDCodec)");
	}
}

void ImageMDCodec::set_preferred_payload_size (Uint16 size) {
	if ((size>=10) && (size<=18330))
		m_preferred_payload_size = size;
	else {
		LOG_ERROR("Trying to set preferred payload to "<<size<<": for ImageMDCodec should be in range [10,18330]");
	}
}

void ImageMDCodec::set_null_pixel_colors(Uint8 r, Uint8 g, Uint8 b) {
	m_null_pixel.set_r(r);
	m_null_pixel.set_g(g);
	m_null_pixel.set_b(b);
}

pixel_container ImageMDCodec::get_null_pixel_colors() {return m_null_pixel;}
