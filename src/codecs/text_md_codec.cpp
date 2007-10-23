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
#include "md_stream.h"
#include "descriptor.h"
#include "../common/data_chunk.h"

TextMDCodec::TextMDCodec() {
	m_flows_number = 1;
	m_descriptors_number = 0;
	m_descr_total_dim = 1;
}

void TextMDCodec::set_flows_number(Uint8 descriptors) {
	m_flows_number = descriptors;
}

Uint8 TextMDCodec::get_flows_number() {
	return m_flows_number;
}

void TextMDCodec::set_descriptor_dimension(Uint16 total_dimension) {
	m_descr_total_dim = total_dimension;
}

void TextMDCodec::code(AbstractStream* stream, MDStream* md_stream)
{
	std::string m_codec_name = "text";
	Uint16 m_payload_size = 8000;
	m_descriptors_number = (stream->get_data_dim()/(m_flows_number*m_payload_size))+1;
	md_stream->init(m_flows_number, m_descriptors_number);
	for (Uint8 i=1; i<=m_flows_number; i++) {
		for (Uint32 j=0; j<m_descriptors_number; j++) {
			Descriptor* descriptor= new Descriptor;
			descriptor->set_hash(stream->get_stream_hash());
			descriptor->set_file_name(stream->get_stream_name()+".mdc");
			descriptor->set_flow_id(i);
			descriptor->set_sequence_number(j);
			descriptor->set_codec_name(m_codec_name);
			descriptor->set_payload_size(m_payload_size);
			descriptor->set_payload(stream->get_data(m_payload_size));
			stream->set_last_current_position(stream->get_last_current_position()+m_payload_size);
			md_stream->set_descriptor(descriptor);
		}
	}
}

void TextMDCodec::decode(const MDStream* md_stream, AbstractStream* stream) {}
