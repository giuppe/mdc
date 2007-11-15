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

TextMDCodec::TextMDCodec() {
	m_seq_counter.push_back(0);
	m_flows_number = 2;
	m_payload_size = 1000;
}

Uint8 TextMDCodec::get_flows_number() {return m_flows_number;}

void TextMDCodec::code(AbstractStream* stream, MDStream* md_stream) {
	Uint32 flow_dimension = (stream->get_data_dim()/m_flows_number)+1;
	m_descriptors_number = (flow_dimension/m_payload_size)+1;
	m_payload_size = (flow_dimension/m_descriptors_number)+1;
	md_stream->init(m_flows_number, m_descriptors_number);
	TextCodecParameters* tcp = new TextCodecParameters();
	Uint64 offset = 0;
	for (Uint8 i=0; i<m_flows_number; i++) {
		for (Uint32 j=0; j<m_descriptors_number; j++) {
			if (stream->get_data_dim()-offset > 0) {
				Descriptor* descriptor= new Descriptor();
				descriptor->set_hash(stream->get_stream_hash());
				descriptor->set_file_name(stream->get_stream_name()+".mdc");
				descriptor->set_flow_id(i);
				descriptor->set_sequence_number(j);
				descriptor->set_codec_name(std::string("text"));
				descriptor->set_codec_parameters_size(tcp->get_size());
				if (descriptor->get_codec_name() != "text")
					descriptor->set_codec_parameter(tcp);
				if (stream->get_data_dim()-offset-1 < m_payload_size)
					m_payload_size = stream->get_data_dim() - offset;
				descriptor->set_payload_size(m_payload_size);
				DataChunk payload; 
				payload+=(stream->get_data(offset, m_payload_size));
				offset += m_payload_size;
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
		m_flows_number = number;
}

void TextMDCodec::set_payload_size (Uint16 size) {
	if ((size>25) || (size<55000))
		m_payload_size = size;
}
