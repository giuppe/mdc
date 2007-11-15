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
	m_flows_number = 64;
	m_payload_size = 1;
}

void TextMDCodec::set_flows_number(Uint8 descriptors) {m_flows_number = descriptors;}
Uint8 TextMDCodec::get_flows_number() {return m_flows_number;}

void TextMDCodec::code(AbstractStream* stream, MDStream* md_stream) {
	m_descriptors_number = (stream->get_data_dim()/(m_flows_number*m_payload_size))+1;
	md_stream->init(m_flows_number, m_descriptors_number);
	bool finished = false;
	TextCodecParameters* tcp = new TextCodecParameters();
	for (Uint8 i=0; i<m_flows_number; i++) {
		for (Uint32 j=0; j<m_descriptors_number; j++) {
			if (stream->get_data_dim()-stream->get_last_current_position() > 0) {
				Descriptor* descriptor= new Descriptor();
				descriptor->set_hash(stream->get_stream_hash());
				descriptor->set_file_name(stream->get_stream_name()+".mdc");
				descriptor->set_flow_id(i);
				descriptor->set_sequence_number(j);
				descriptor->set_codec_name(std::string("text"));
				if (descriptor->get_codec_name() != "text") {
					descriptor->set_codec_parameters_size(tcp->get_size());
					descriptor->set_codec_parameter(tcp);
				}
				if (stream->get_data_dim()-stream->get_last_current_position()-1 < m_payload_size) {
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
	if (!md_stream->is_empty()) {
		std::string name;
		DataChunk* dc = new DataChunk();
		Uint32 valid_descriptor_counter = md_stream->get_valid_descriptors_number();
		for (Uint8 i=0; i<md_stream->get_flows_number(); i++)
			for (Uint32 j=0; j<md_stream->get_sequences_number(); j++) {
				Descriptor* descriptor = new Descriptor();
				bool another_descriptor = false;
				if (md_stream->get_descriptor(i, j, descriptor) && (descriptor->get_codec_name()=="text")) {
					name = descriptor->get_file_name();
					Uint8 m_descriptor_flow_id = descriptor->get_flow_id();
					Uint32 m_descriptor_seq_number = descriptor->get_sequence_number();
					if (m_flows_id.empty() && (!another_descriptor)) {
						m_flows_id.push_back(m_descriptor_flow_id);
						if (m_descriptor_seq_number >= (m_seq_counter[m_flows_id[0]])) {
							(*dc) += *(descriptor->get_payload());
							m_seq_counter[m_flows_id[0]] = m_descriptor_seq_number;
							valid_descriptor_counter--;
							another_descriptor = true;
						}
					}
					else
						for (Uint8 k=0; k<m_flows_id.size(); k++)
							if ((m_descriptor_flow_id>m_flows_id[k]) && (m_descriptor_seq_number<m_seq_counter[m_flows_id[k]]) && (!another_descriptor)) {
								m_flows_id.push_back(m_descriptor_flow_id);
								(*dc) += *(descriptor->get_payload());
								m_seq_counter[m_flows_id[k]] = m_descriptor_seq_number;
								valid_descriptor_counter--;
								another_descriptor = true;
							}
							else if ((m_descriptor_flow_id==m_flows_id[k]) && (valid_descriptor_counter>0) && (!another_descriptor)) {
								(*dc) += *(descriptor->get_payload());
								m_seq_counter[m_flows_id[k]] = m_descriptor_seq_number;
								valid_descriptor_counter--;
								another_descriptor = true;
							}
				}
			}
		stream->set_stream_name(name);
		stream->update_stream_hash();
		stream->set_data(*dc);
	}
}

TextMDCodec::~TextMDCodec() {}
