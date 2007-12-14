/***************************************************************************
                      descriptor.cpp  -  MDC Descriptor
                             -------------------
    begin                : Jul 13, 2007
    copyright          : (C) 2007 by Giuseppe D'Aqui'
    email                : giuseppe.da@gmail.com
 ***************************************************************************/

/***************************************************************************
 *                                                                                                                 
 *   This program is free software; you can redistribute it and/or modify  
 *   it under the terms of the GNU General Public License, Version 2,        
 *   as published by the Free Software Foundation.                                  
 *                                                                                                                 
 ***************************************************************************/

#include "descriptor.h"
#include "../../common/data/mem_data_chunk.h"
#include "../../messages/mdc_message.h"
#include "../codec_parameters_factory.h"


Descriptor::Descriptor() {}
Uint8 Descriptor::get_flow_id() const {return m_flow_id;}
void Descriptor::set_flow_id(Uint8 id) {m_flow_id = id;}
Uint32 Descriptor::get_sequence_number() const {return m_sequence_number;}
void Descriptor::set_sequence_number(Uint32 seq_num) {m_sequence_number = seq_num;}
void Descriptor::set_codec_name(const string& codec_name) {m_codec_name = codec_name;}
string Descriptor::get_codec_name() const {return m_codec_name;}
AbstractCodecParameters* Descriptor::get_codec_parameter() const {return m_codec_parameters;}
void Descriptor::set_codec_parameter(AbstractCodecParameters* acp) {m_codec_parameters = acp;}
Descriptor::~Descriptor() {delete m_codec_parameters;}




MemDataChunk& Descriptor::serialize() const {
	MemDataChunk* result = new MemDataChunk();
	MDCMessage msg;
	msg.set_type_string("DESC");
	(*result)+=&msg.serialize();
	result->append_cstring(m_complete_stream_md5_hash.c_str());
	result->append_Uint8(m_flow_id);
	result->append_Uint32(m_sequence_number);
	result->append_cstring(m_codec_name.c_str());
	MemDataChunk temp_codec_parameters;
	temp_codec_parameters += &m_codec_parameters->serialize();
	result->append_Uint32(temp_codec_parameters.get_lenght());
	(*result)+=&temp_codec_parameters;
	Uint16 payload_size = m_payload.get_lenght();
	result->append_Uint16(payload_size);
	(*result)+=&this->m_payload;
	return (*result);
}




void Descriptor::deserialize(const IDataChunk* data) {
	if (data->get_lenght() > 0) {
		MemDataChunk* temp_dc = new MemDataChunk();
		temp_dc->operator +=(data);
		char* hash;
		char* codec_name;
		MemDataChunk preamble;
		temp_dc->extract_head(8, preamble);
		MDCMessage msg;
		msg.deserialize(&preamble);
		if (string(msg.get_type_string()) == string("DESC")) {
			temp_dc->extract_head(hash);
			m_complete_stream_md5_hash = hash;
			temp_dc->extract_head(m_flow_id);
			temp_dc->extract_head(m_sequence_number);
			temp_dc->extract_head(codec_name);
			m_codec_name= codec_name;
			Uint32 codec_parameters_size = 0;
			temp_dc->extract_head(codec_parameters_size);
			MemDataChunk* codec_parameters_dc = new MemDataChunk();
			temp_dc->extract_head(codec_parameters_size, *codec_parameters_dc);
			m_codec_parameters=CodecParametersFactory::create_codec_parameters(m_codec_name);
			m_codec_parameters->deserialize(codec_parameters_dc);
			delete codec_parameters_dc;
			Uint16 payload_size = 0;
			temp_dc->extract_head(payload_size);
			temp_dc->extract_head((Uint32)payload_size, m_payload);
		}
	}
}




Uint16 Descriptor::get_payload_size() const {return m_payload.get_lenght();}




void Descriptor::set_payload(MemDataChunk& payload)
{
	m_payload.erase();
	m_payload+=&payload;
}




MemDataChunk* Descriptor::get_payload() const
{
	MemDataChunk* payload = new MemDataChunk();
	(*payload)+=&m_payload;
	return payload;
}




Uint32 Descriptor::get_codec_parameters_size() const 
{
	return m_codec_parameters->get_size();
}





string Descriptor::get_stream_id() const
{
	return m_complete_stream_md5_hash;
}

void Descriptor::set_stream_id(string stream_id)
{
	m_complete_stream_md5_hash = stream_id;
}
