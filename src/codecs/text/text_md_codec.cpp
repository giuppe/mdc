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
	m_flows_number = 3;
	m_descriptors_number = 0;
	m_seq_counter.push_back(0);
}

void TextMDCodec::set_flows_number(Uint8 descriptors) {m_flows_number = descriptors;}
Uint8 TextMDCodec::get_flows_number() {return m_flows_number;}

void TextMDCodec::code(AbstractStream* stream, MDStream* md_stream) {
	std::string m_codec_name = "text";
	Uint16 m_payload_size = 13;
	m_descriptors_number = (stream->get_data_dim()/(m_flows_number*m_payload_size))+1;
	md_stream->init(m_flows_number, m_descriptors_number);
	bool finished = false;
	for (Uint8 i=0; i<m_flows_number; i++) {
		for (Uint32 j=0; j<m_descriptors_number; j++) {
			if (stream->get_data_dim()-stream->get_last_current_position() > 0) {
				Descriptor* descriptor= new Descriptor();
				descriptor->set_hash(stream->get_stream_hash());
				descriptor->set_file_name(stream->get_stream_name()+".mdc");
				descriptor->set_flow_id(i);
				descriptor->set_sequence_number(j);
				descriptor->set_codec_name(m_codec_name);
				TextCodecParameters* tcp = new TextCodecParameters();
				descriptor->set_codec_parameters_size(tcp->get_size());
				descriptor->set_codec_parameter(tcp);
				if (stream->get_data_dim()-stream->get_last_current_position() < m_payload_size) {
					m_payload_size = stream->get_data_dim() - stream->get_last_current_position();
					finished = true;
				}
				descriptor->set_payload_size(m_payload_size);
				DataChunk* payload = &(stream->get_data(m_payload_size));
				descriptor->set_payload(*payload);
				md_stream->set_descriptor(descriptor);
				if (finished) return;
			}
		}
	}
}

void TextMDCodec::decode(const MDStream* md_stream, AbstractStream* stream) {
	if (!md_stream->is_empty())
		for (Uint8 i=0; i<m_flows_number; i++)
			for (Uint32 j=0; j<m_descriptors_number; j++) {
				Descriptor* descriptor = new Descriptor();
				if (md_stream->get_descriptor(i, j, descriptor) && (descriptor->get_codec_name()=="text")) {
					Uint8 m_descriptor_flow_id = descriptor->get_flow_id();
					Uint32 m_descriptor_seq_number = descriptor->get_sequence_number();
					if (m_flows_id.empty()) {
						m_flows_id.push_back(m_descriptor_flow_id);
						if (m_descriptor_seq_number >= (m_seq_counter[m_flows_id[0]])) {
							DataChunk* dc = new DataChunk();
							(*dc) += *(descriptor->get_payload());
							m_seq_counter[m_flows_id[0]] = m_descriptor_seq_number;
						}
					}
					else
						for (Uint8 k=0; k<m_flows_id.size(); k++)
							if (m_descriptor_flow_id == m_flows_id[k]) {
								if (m_descriptor_seq_number < m_seq_counter[m_flows_id[k]])
									m_flows_id.push_back(m_descriptor_flow_id);
								DataChunk* dc = new DataChunk();
								(*dc) += *(descriptor->get_payload());
								m_seq_counter[m_flows_id[k]] = m_descriptor_seq_number;
							}
				}
			}
}

TextMDCodec::~TextMDCodec() {}
