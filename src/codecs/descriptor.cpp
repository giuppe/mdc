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
#include <cassert>

Uint8 Descriptor::get_flow_id() const {return m_flow_id;}
void Descriptor::set_flow_id(Uint8 id) {m_flow_id = id;}
Uint32 Descriptor::get_sequence_number() const {return m_sequence_number;}
void Descriptor::set_sequence_number(Uint32 seq_num) {m_sequence_number = seq_num;}
std::string Descriptor::get_file_name() const {return m_file_name;}
void Descriptor::set_file_name(const std::string& file_name) {m_file_name = file_name;}
std::string Descriptor::get_hash() const {return m_hash;}
void Descriptor::set_hash(const std::string& hash) {m_hash = hash;}
void Descriptor::set_codec_name(const std::string& codec_name) {m_codec_name = codec_name;}
std::string Descriptor::get_codec_name() const {return m_codec_name;}
AbstractCodecParameters* Descriptor::get_codec_parameter() const {return m_codec_parameters;}
void Descriptor::set_codec_parameter(AbstractCodecParameters* acp) {m_codec_parameters = acp;}

Descriptor::~Descriptor() {
	delete m_codec_parameters;
	delete[] m_payload;
}

DataChunk& Descriptor::serialize() const
{
	DataChunk* result = new DataChunk();
	MDCMessage msg;
	msg.set_type_string("DESC");
	(*result)+=msg.serialize();
	result->append(this->m_hash.c_str());
	result->append(this->m_file_name.c_str());
	result->append(m_flow_id);
	result->append(this->m_sequence_number);
	result->append(this->m_codec_name.c_str());
	result->append(this->m_codec_parameters_size);
	(*result)+=m_codec_parameters->serialize();
	result->append(this->m_payload_size);
	result->append(this->m_payload_size, this->m_payload);
	return (*result);
}

void Descriptor::deserialize(const DataChunk& data) {assert(!"This function is a stub.");}
void Descriptor::set_payload_size(Uint32 psize) {m_payload_size = psize;}
Uint32 Descriptor::get_payload_size() {return m_payload_size;}
void Descriptor::set_payload(DataChunk& payload) {m_payload = payload.get_data();}

DataChunk* Descriptor::get_payload() {
	DataChunk* payload = new DataChunk;
	payload->append(m_payload_size, m_payload);
	return payload;
}

Uint32 Descriptor::get_codec_parameters_size() {return m_codec_parameters_size;}
void Descriptor::set_codec_parameters_size(Uint32 size) {m_codec_parameters_size = size;}
