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
#include "../abstract_md_codec.h"
#include "../codec_registry.h"


Descriptor::Descriptor() {}
Uint8 Descriptor::get_flow_id() const {return m_flow_id;}
void Descriptor::set_flow_id(Uint8 id) {m_flow_id = id;}
Uint32 Descriptor::get_sequence_number() const {return m_sequence_number;}
void Descriptor::set_sequence_number(Uint32 seq_num) {m_sequence_number = seq_num;}
void Descriptor::set_codec_name(const string& codec_name) 
{
	//m_codec_name = codec_name;
	AbstractMDCodec* temp_codec;
	if(!CodecRegistry::instance()->get_codec(codec_name, temp_codec))
	{
		LOG_ERROR("Cannot find codec "<<codec_name);
		return;
	}
	m_codec_code = temp_codec->get_codec_type_code();
}

string Descriptor::get_codec_name() const 
{
	AbstractMDCodec* temp_codec;
	if(!CodecRegistry::instance()->get_codec(m_codec_code, temp_codec))
	{
		LOG_ERROR("Cannot find codec of type "<<m_codec_code);
		return "";
	}
	
	return temp_codec->get_codec_type_string();
}

AbstractCodecParameters* Descriptor::get_codec_parameter() const {return m_codec_parameters;}
void Descriptor::set_codec_parameter(AbstractCodecParameters* acp) {m_codec_parameters = acp;}
Descriptor::~Descriptor() {delete m_codec_parameters;}




MemDataChunk& Descriptor::serialize() const {
	MemDataChunk* result = new MemDataChunk();
	MDCMessage msg;
	msg.set_type_string("DESC");
	(*result)+=&msg.serialize();
	MemDataChunk temp_stream_id; 
	temp_stream_id.append_cstring(m_complete_stream_md5_hash.c_str());
	result->append_data(32, temp_stream_id.get_data());
	
	result->append_Uint8(m_flow_id);
	result->append_Uint32(m_sequence_number);
	//result->append_cstring(m_codec_name.c_str());
	result->append_Uint8(m_codec_code);
	MemDataChunk temp_codec_parameters;
	temp_codec_parameters += &m_codec_parameters->serialize();
	result->append_Uint32(temp_codec_parameters.get_lenght());
	(*result)+=&temp_codec_parameters;
	Uint16 payload_size = m_payload.get_lenght();
	result->append_Uint16(payload_size);
	(*result)+=&this->m_payload;
	return (*result);
}




bool Descriptor::deserialize(const IDataChunk* data) {
	if (data->get_lenght() == 0) {
		return false;
	}
	DataChunkIterator temp_dc = data->get_iterator();

	Uint8* hash = new Uint8[33];
	memset(hash, 0, 33);
	//char* codec_name;
	Uint8 codec_code;
	IDataChunk* preamble;
	temp_dc.get_data_chunk(8, preamble);
	MDCMessage msg;
	if(!msg.deserialize(preamble))
	{
		return false;
	}
	if (string(msg.get_type_string()) != string("DESC")) 
	{
		return false;
	}
	
	if(!temp_dc.get_data(32,hash))
	{
		return false;
	}
	m_complete_stream_md5_hash =(char*) hash;
	if(!temp_dc.get_Uint8(m_flow_id))
	{
		return false;
	}
	if(!temp_dc.get_Uint32(m_sequence_number))
	{
		return false;
	}

	//if(!temp_dc.get_cstring(codec_name))
	if(!temp_dc.get_Uint8(codec_code))
	{
		return false;
	}
	m_codec_code= codec_code;
	
	Uint32 codec_parameters_size = 0;
	if(!temp_dc.get_Uint32(codec_parameters_size))
	{
		return false;
	}
	IDataChunk* codec_parameters_dc;
	if(!temp_dc.get_data_chunk(codec_parameters_size, codec_parameters_dc))
	{
		return false;
	}
	m_codec_parameters=CodecParametersFactory::create_codec_parameters(m_codec_code);
	if(!m_codec_parameters->deserialize(codec_parameters_dc))
	{
		return false;
	}
	delete codec_parameters_dc;
	Uint16 payload_size = 0;
	if(!temp_dc.get_Uint16(payload_size))
	{
		return false;
	}
	IDataChunk* temp_payload;
	if(!temp_dc.get_data_chunk((Uint32)payload_size, temp_payload))
	{
		return false;
	}
	m_payload.erase();
	m_payload += temp_payload;
	return true;

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
