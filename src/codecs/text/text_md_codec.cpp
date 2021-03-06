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
#include "defs.h"
#include "text_stream.h"
#include "../mdc/md_stream.h"
#include "../mdc/descriptor.h"
#include "../../common/data/mem_data_chunk.h"
#include "text_codec_parameters.h"
#include <cmath>

TextMDCodec::TextMDCodec() {
	m_flows_number = 2;
	m_preferred_payload_size = 1000;
}

void TextMDCodec::code(AbstractStream* stream, MDStream* md_stream) const {
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
				descriptor->set_codec_name(string("text"));
				TextCodecParameters* tcp = new TextCodecParameters();
				descriptor->set_codec_parameter(tcp);
				MemDataChunk payload;
				Uint64 k;
				for (k=0; k<max_payload_size; k++)
					if (offset+i+k+m_flows_number < stream_size)
						payload += &stream->get_data(offset+i+(k*m_flows_number), 1);
				offset += m_flows_number*k;
				descriptor->set_payload(payload);
				md_stream->set_descriptor(descriptor);
			}
		}
	}
}

void TextMDCodec::decode(const MDStream* md_stream, AbstractStream* stream) const {
	if (md_stream->is_empty()) 
	{
		return;
	}
	LOG_INFO("Decoding...");
	MemDataChunk* dc = new MemDataChunk();
	vector<Uint8> took_stream;
	Uint8 flows_number = md_stream->get_flows_number();
	LOG_INFO("Flows number: "<<flows_number);
	Uint32 sequences_number = md_stream->get_sequences_number();
	LOG_INFO("Sequences number: "<<sequences_number);
	Uint64 max_dimension = 0;
	for (Uint8 i=0; i<flows_number; i++) 
	{
		Uint64 offset = 0;
		Uint16 payload_size = 0;
		for (Uint32 j=0; j<sequences_number; j++) 
		{
			Descriptor* descriptor = new Descriptor();
			if(!(descriptor->get_codec_name()=="text"))
			{
				continue;
			}

			if (md_stream->get_descriptor(i, j, descriptor)) 
			{
				payload_size = descriptor->get_payload_size();
				if (md_stream->is_valid(descriptor->get_flow_id(), descriptor->get_sequence_number())) 
				{
					(*dc) += (descriptor->get_payload());
					took_stream.resize(flows_number*sequences_number*(payload_size+1));
					Uint8 current_received_data;
					Uint64 k;
					for (k=0; k<payload_size; k++) {
						dc->extract_head(current_received_data);
						if (current_received_data != 0) {
							Uint64 locate_position = offset+i+(k*flows_number);
							took_stream[locate_position] = current_received_data;
							if (locate_position > max_dimension)
								max_dimension = locate_position;
						}
					}
					offset += flows_number*k;
				}
			}
			else 
			{
				Uint64 k;
				for (k=0; k<payload_size; k++) {
					Uint64 locate_position = offset+i+(k*flows_number);
					took_stream[locate_position] = ' ';
				}
				offset += flows_number*k;
			}
		}
	}
	MemDataChunk* taken_dc = new MemDataChunk();
	Uint8* temp_container = new Uint8[max_dimension+1];
	for (Uint64 i=0; i<max_dimension+1; i++)
		temp_container[i] = took_stream[i];
	taken_dc->append_data(max_dimension+1, temp_container);
	stream->set_data(*taken_dc);

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
