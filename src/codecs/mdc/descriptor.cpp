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
#include "../../common/data_chunk.h"
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




DataChunk& Descriptor::serialize() const {
	DataChunk* result = new DataChunk();
	MDCMessage msg;
	msg.set_type_string("DESC");
	(*result)+=msg.serialize();
	result->append(m_complete_stream_md5_hash.c_str());
	result->append(m_flow_id);
	result->append(m_sequence_number);
	result->append(m_codec_name.c_str());
	DataChunk temp_codec_parameters;
	temp_codec_parameters += m_codec_parameters->serialize();
	result->append(temp_codec_parameters.get_lenght());
	(*result)+=temp_codec_parameters;
	Uint16 payload_size = m_payload.get_lenght();
	result->append(payload_size);
	(*result)+=this->m_payload;
	return (*result);
}




void Descriptor::deserialize(const DataChunk& data) {
	if (data.get_lenght() > 0) {
		DataChunk* temp_dc = new DataChunk();
		temp_dc->operator +=(data);
		char* hash;
		char* codec_name;
		DataChunk preamble;
		temp_dc->extract_head(8, preamble);
		MDCMessage msg;
		msg.deserialize(preamble);
		if (string(msg.get_type_string()) == string("DESC")) {
			temp_dc->extract_head(hash);
			m_complete_stream_md5_hash = hash;
			temp_dc->extract_head(m_flow_id);
			temp_dc->extract_head(m_sequence_number);
			temp_dc->extract_head(codec_name);
			m_codec_name= codec_name;
			Uint32 codec_parameters_size = 0;
			temp_dc->extract_head(codec_parameters_size);
			DataChunk* codec_parameters_dc = new DataChunk();
			temp_dc->extract_head(codec_parameters_size, *codec_parameters_dc);
			m_codec_parameters=CodecParametersFactory::create_codec_parameters(m_codec_name);
			m_codec_parameters->deserialize(*codec_parameters_dc);
			delete codec_parameters_dc;
			Uint16 payload_size = 0;
			temp_dc->extract_head(payload_size);
			temp_dc->extract_head((Uint32)payload_size, m_payload);
		}
	}
}




Uint16 Descriptor::get_payload_size() const {return m_payload.get_lenght();}




void Descriptor::set_payload(DataChunk& payload)
{
	m_payload.erase();
	m_payload+=payload;
}




DataChunk* Descriptor::get_payload() const
{
	DataChunk* payload = new DataChunk();
	(*payload)+=m_payload;
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
