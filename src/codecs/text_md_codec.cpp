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
#include "text_codec_parameters.h"
#include <vector>

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
	for (Uint8 i=0; i<m_flows_number; i++) {
		for (Uint32 j=0; j<m_descriptors_number; j++) {
			Descriptor* descriptor= new Descriptor();
			descriptor->set_hash(stream->get_stream_hash());
			descriptor->set_file_name(stream->get_stream_name()+".mdc");
			descriptor->set_flow_id(i);
			descriptor->set_sequence_number(j);
			descriptor->set_codec_name(m_codec_name);
			TextCodecParameters* tcp = new TextCodecParameters();
			descriptor->set_codec_parameter(tcp);
			descriptor->set_payload_size(m_payload_size);
			DataChunk* payload = &(stream->get_data(m_payload_size));
			descriptor->set_payload(*payload);
			stream->set_last_current_position(stream->get_last_current_position()+m_payload_size);
			md_stream->set_descriptor(descriptor);
		}
	}
}

void TextMDCodec::decode(const MDStream* md_stream, AbstractStream* stream) {//FIXME
	if (!md_stream->is_empty())
		for (Uint8 i=0; i<m_flows_number; i++)
			for (Uint32 j=0; j<m_descriptors_number; j++) {
				Descriptor* descriptor = new Descriptor();
				if (md_stream->get_descriptor(i, j, descriptor) && (descriptor->get_codec_name()=="text")) {
					Uint8 m_descriptor_flow_id = descriptor->get_flow_id();
					Uint32 m_descriptor_seq_number = descriptor->get_sequence_number();
					if (m_flows_id.empty()) {//create only 1 new flow - first step
						m_flows_id.push_back(m_descriptor_flow_id);//insert flow_id into first position
						if (m_descriptor_seq_number >= (m_seq_counter.at(m_flows_id.at(0)))) {
							DataChunk* dc = descriptor->get_payload();//or write directly to output file?
							m_seq_counter.at(m_flows_id.at(0)) = m_descriptor_seq_number;
							return;
						}
					}
					else
						for (Uint8 k=0; k<m_flows_id.size(); k++)
							if (m_descriptor_flow_id == m_flows_id.at(k))//this is the current flow_id
								if (m_descriptor_seq_number >= m_seq_counter.at(m_flows_id.at(k))) {
									DataChunk* dc = descriptor->get_payload();//or write directly to output file?
									m_seq_counter.at(m_flows_id.at(k)) = m_descriptor_seq_number;
									return;
								}
								else {//it's a new flow's descriptor
									m_flows_id.push_back(m_descriptor_flow_id);//insert new flow_id
									DataChunk* dc = descriptor->get_payload();//or write directly to output file?
									m_seq_counter.at(m_flows_id.at(k)) = m_descriptor_seq_number;
								}
				}
			}
}
