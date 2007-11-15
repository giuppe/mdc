/***************************************************************************
                   text_md_codec.cpp  -  Manage text codec
                             -------------------
    begin                : Oct 5, 2007
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

#include "text_md_codec.h"
#include <string>
#include "defs.h"
#include "text_stream.h"
#include "../md_stream.h"
#include "../descriptor.h"
#include "../../common/data_chunk.h"
#include "text_codec_parameters.h"
#include <vector>
#include <cmath>

TextMDCodec::TextMDCodec() {
	m_seq_counter.push_back(0);
	m_flows_number = 2;
	m_preferred_payload_size = 1000;
}


void TextMDCodec::code(AbstractStream* stream, MDStream* md_stream) {
	Uint32 stream_size = stream->get_data_dim();
	Uint32 flow_dimension = (stream_size/m_flows_number)+1;
	
	Uint32 descriptors_number = (Uint32)ceil(((double)flow_dimension)/((double)m_preferred_payload_size));
	Uint16 max_payload_size = (flow_dimension/descriptors_number)+1;
	md_stream->init(m_flows_number, descriptors_number);
	
	Uint64 offset = 0;
	for (Uint8 i=0; i<m_flows_number; i++) {
		for (Uint32 j=0; j<descriptors_number; j++) {
			if((i==1)&&(j==161))
			{
				Uint32 temp;
				temp = 1;
			}
			if (stream_size-offset > 0) {
				Descriptor* descriptor= new Descriptor();
				descriptor->set_hash(stream->get_stream_hash());
				descriptor->set_file_name(stream->get_stream_name()+".mdc");
				descriptor->set_flow_id(i);
				descriptor->set_sequence_number(j);
				descriptor->set_codec_name(std::string("text"));
				//descriptor->set_codec_parameters_size(tcp->get_size());
				TextCodecParameters* tcp = new TextCodecParameters();
				descriptor->set_codec_parameter(tcp);
				Uint16 payload_size;
				if (stream_size-offset-1 < max_payload_size)
				{
					payload_size = stream_size - offset;
				}
				else
				{
					payload_size = max_payload_size;
				}
				//descriptor->set_payload_size(m_payload_size);
				DataChunk payload; 
				payload+=(stream->get_data(offset, payload_size));
				offset += payload_size;
				descriptor->set_payload(payload);
				md_stream->set_descriptor(descriptor);
			}
		}
	}
}

void TextMDCodec::decode(const MDStream* md_stream, AbstractStream* stream) {
	if (!md_stream->is_empty()) {
		std::string name;
		DataChunk* dc = new DataChunk();
		for (Uint8 i=0; i<md_stream->get_flows_number(); i++)
			for (Uint32 j=0; j<md_stream->get_sequences_number(); j++) {
				Descriptor* descriptor = new Descriptor();
				if (md_stream->get_descriptor(i, j, descriptor) && (descriptor->get_codec_name()=="text")) {
					name = descriptor->get_file_name();
					if (md_stream->is_valid(descriptor->get_flow_id(), descriptor->get_sequence_number()))
						(*dc) += *(descriptor->get_payload());
				}
			}
		stream->set_stream_name(name);
		stream->update_stream_hash();
		stream->set_data(*dc);
	}
}

TextMDCodec::~TextMDCodec() {}

void TextMDCodec::set_flows_number (Uint8 number) {
	if ((number>0) || (number<65))
	{
		m_flows_number = number;
	}
	else
	{
		LOG_ERROR("Trying to set flows number to "<<number<<">64 (Max flows number for TextMDCodec)");
	}
}

void TextMDCodec::set_preferred_payload_size (Uint16 size) {
	if ((size>25) || (size<55000))
	{
		m_preferred_payload_size = size;
	}
	else
	{
		LOG_ERROR("Trying to set preferred payload to "<<size<<": for TextMDCodec should be in range [25,55000]");
	}
}
