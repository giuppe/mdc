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
#include "../mdc/md_stream.h"
#include "../mdc/descriptor.h"
#include "../../common/data_chunk.h"
#include "text_codec_parameters.h"
#include <vector>
#include <cmath>

TextMDCodec::TextMDCodec() {
	m_seq_counter.push_back(0);
	m_flows_number = 2;
	m_preferred_payload_size = 1000;
}

void TextMDCodec::code(AbstractStream* stream, MDStream* md_stream) const {
	Uint32 stream_size = stream->get_data_dim();
	Uint32 flow_dimension = (stream_size/m_flows_number)+1;
	Uint32 descriptors_number = (Uint32)ceil(((double)flow_dimension)/((double)m_preferred_payload_size));
	Uint16 max_payload_size = (flow_dimension/descriptors_number)+1;
	md_stream->init(m_flows_number, descriptors_number);
	Uint64 offset = 0;
	for (Uint8 i=0; i<m_flows_number; i++) {
		for (Uint32 j=0; j<descriptors_number; j++) {
			if (stream_size-offset > 0) {
				Descriptor* descriptor= new Descriptor();
				descriptor->set_hash(stream->get_stream_hash());
				descriptor->set_file_name(stream->get_stream_name()+".mdc");
				descriptor->set_flow_id(i);
				descriptor->set_sequence_number(j);
				descriptor->set_codec_name(std::string("text"));
				TextCodecParameters* tcp = new TextCodecParameters();
				descriptor->set_codec_parameter(tcp);
				DataChunk payload;
				for (Uint64 k=0; k<max_payload_size; k++)
					payload += stream->get_data(offset+(max_payload_size*k), 1);
				offset++;
				descriptor->set_payload(payload);
				md_stream->set_descriptor(descriptor);
			}
		}
	}
}

void TextMDCodec::decode(const MDStream* md_stream, AbstractStream* stream) const {
	if (!md_stream->is_empty()) {
		std::string name;
		DataChunk* dc = new DataChunk();
		std::vector<Uint8> taken_stream;
		Uint64 offset = 0;
		Uint8 last_valid_flow_number = 0;
		Uint32 last_valid_sequence_number = 0;
		Uint8 flows_number = md_stream->get_flows_number();
		Uint32 sequences_number = md_stream->get_sequences_number();
		for (Uint8 i=0; i<flows_number; i++)
			for (Uint32 j=0; j<sequences_number; j++) {
				Descriptor* descriptor = new Descriptor();
				Uint32 descriptors_not_valid = 0;
				if (md_stream->get_descriptor(i, j, descriptor) && (descriptor->get_codec_name()=="text")) {
					name = descriptor->get_file_name();
					if (taken_stream.size() == 0) {
						taken_stream.resize(flows_number*sequences_number*descriptor->get_payload_size());
						for (Uint64 k=0; k<taken_stream.size(); k++)
							taken_stream[k] = 0;
					}
					if (md_stream->is_valid(descriptor->get_flow_id(), descriptor->get_sequence_number())) {
						(*dc) += *(descriptor->get_payload());
						Uint8* current_received_data = dc->get_data();
						for (Uint64 k=0; k<descriptor->get_payload_size(); k++)
							taken_stream[offset+(descriptor->get_payload_size()*k)] = current_received_data[k];
						last_valid_sequence_number = j;
						last_valid_flow_number = i;
					}
				}
				else {
					if ((last_valid_flow_number!=0) || (last_valid_sequence_number!=0)) {
						for (Uint8 k=last_valid_flow_number; k<=i; k++) {
							if (last_valid_sequence_number < j)
								for (Uint32 m=last_valid_sequence_number; m<=j; m++)
									descriptors_not_valid++;
							else if (last_valid_sequence_number > j)
								for (Uint32 m=j; m<=last_valid_sequence_number; m++)
									descriptors_not_valid++;
						}
						descriptors_not_valid -= 2;
					}
					else offset++;
				}
				offset += descriptors_not_valid;
			}
		stream->set_stream_name(name);
		stream->update_stream_hash();
		DataChunk* taken_dc = new DataChunk();
		Uint8* temp_container;
		for (Uint64 i=0; i<taken_stream.size(); i++)
			temp_container[i] = taken_stream[i];
		taken_dc->append(taken_stream.size(), temp_container);
		stream->set_data(*taken_dc);
	}
}

TextMDCodec::~TextMDCodec() {}

void TextMDCodec::set_flows_number (Uint8 number) {
	if ((number>0) && (number<65))
		m_flows_number = number;
	else {
		LOG_ERROR("Trying to set flows number to "<<number<<">64 (Max flows number for TextMDCodec)");
	}
}

void TextMDCodec::set_preferred_payload_size (Uint16 size) {
	if ((size>25) && (size<55000))
		m_preferred_payload_size = size;
	else {
		LOG_ERROR("Trying to set preferred payload to "<<size<<": for TextMDCodec should be in range [25,55000]");
	}
}
