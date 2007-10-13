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
#include <vector>

void TextMDCodec::set_flows_number (Uint8 descriptors) {
	m_flows_number = descriptors;
}

Uint8 TextMDCodec::get_flows_number () {
	return m_flows_number;
}

void TextMDCodec::code(const AbstractStream* stream, MDStream* md_stream) 
{
	//settare i flussi e derivare i descrittori
	std::vector<Uint32> m_seq;
	std::vector<Descriptor> descriptors;
	for (Uint8 i=1; i<=m_flows_number; i++) {
		Descriptor* descriptor(i)= new Descriptor;
		descriptor(i)->set_file_name(stream->get_stream_name()+".mdc");
		descriptor(i)->set_flow_id(i);
		descriptor(i)->set_codec_name("text");
		Uint32 m_descriptor_dim = Uint32(stream->get_payload_size() / m_descriptor_number);
		if (i-m_descriptor_number == 0)
			m_descriptor_dim = Uint32(stream->get_payload_size() - (descriptor_dim * i));
		descriptor(i)->set_payload_size(m_descriptor_dim);
		Uint32 m_last_position = 0;
		while (m_last_position<=m_descriptor_dim) {
			stream = (dynamic_cast<const TextStream*>(stream))->get_characters(m_last_position, m_last_position+descriptor_dim);
			m_last_position++;
		}
		descriptor(i)->set_sequence_number(m_seq[i]);
		m_seq[i]++;
		DataChunk payload = descriptor(i)->get_payload();
		descriptor(i)->set_payload(payload);
		descriptor(i)->set_hash(stream->get_stream_hash());
		md_stream->set_descriptor(descriptor(i));
	}
}

void TextMDCodec::decode(const MDStream* md_stream, AbstractStream* stream) {}
