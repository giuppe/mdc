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
#include "../common/data_chunk.h"
#include "../messages/mdc_message.h"
#include "codec_parameters_factory.h"
#include <cassert>
#include <string>

Descriptor::Descriptor() {
	m_total_dimension = 0;
	//m_codec_parameters_size = 0;
}

Uint8 Descriptor::get_flow_id() const {return m_flow_id;}
void Descriptor::set_flow_id(Uint8 id) {m_flow_id = id;}
Uint32 Descriptor::get_sequence_number() const {return m_sequence_number;}
void Descriptor::set_sequence_number(Uint32 seq_num) {m_sequence_number = seq_num;}
std::string Descriptor::get_file_name() const {return m_file_name;}

void Descriptor::set_file_name(const std::string& file_name) {
	m_file_name = file_name;
	m_total_dimension += (file_name.size()+1);
}

std::string Descriptor::get_hash() const {return m_hash;}

void Descriptor::set_hash(const std::string& hash) {
	m_hash = hash;
	m_total_dimension += (hash.size()+1);
}

void Descriptor::set_codec_name(const std::string& codec_name) {
	m_codec_name = codec_name;
	m_total_dimension += (codec_name.size()+1);
}

std::string Descriptor::get_codec_name() const {return m_codec_name;}
AbstractCodecParameters* Descriptor::get_codec_parameter() const {return m_codec_parameters;}

void Descriptor::set_codec_parameter(AbstractCodecParameters* acp) {
	m_codec_parameters = acp;
	m_total_dimension += m_codec_parameters->get_size();
}

Descriptor::~Descriptor() {
		delete m_codec_parameters;

}

DataChunk& Descriptor::serialize() const {
	DataChunk* result = new DataChunk();
	MDCMessage msg;
	msg.set_type_string("DESC");
	(*result)+=msg.serialize();
	result->append(m_hash.c_str());
	result->append(m_file_name.c_str());
	result->append(m_flow_id);
	result->append(m_sequence_number);
	result->append(m_codec_name.c_str());
	DataChunk temp_codec_parameters;
	temp_codec_parameters += m_codec_parameters->serialize();
	result->append(temp_codec_parameters.get_lenght());
	(*result)+=temp_codec_parameters;
	result->append(m_payload.get_lenght());
	(*result)+=this->m_payload;
	return (*result);
}

void Descriptor::deserialize(const DataChunk& data) {
	if (data.get_lenght() > 0) {
		DataChunk* temp_dc = new DataChunk();
		temp_dc->operator +=(data);
		
		char* file_name;
		char* file_hash;
		char* codec_name;
				
		DataChunk preamble;
		temp_dc->extract_head(8, preamble);
		MDCMessage msg;
		msg.deserialize(preamble);
		if (msg.get_type_string() == "DESC") {
			temp_dc->extract_head(file_hash);
			m_hash = file_hash;
			temp_dc->extract_head(file_name);
			m_file_name = file_name;
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

//void Descriptor::set_payload_size(Uint16 psize) {m_payload_size = psize;}
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

/*
void Descriptor::set_codec_parameters_size(Uint32 size)
{
	m_codec_parameters_size = size;
}
*/

Uint16 Descriptor::get_descriptor_total_dimension() 
{
	return (m_total_dimension+get_codec_parameters_size()+15+m_payload.get_lenght());
}
