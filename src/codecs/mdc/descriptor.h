/***************************************************************************
                          descriptor.h  -  MDC Descriptor class
                             -------------------
    begin                : Jul 13 2007
    copyright          : (C) 2007 by Giuseppe D'Aqui'
    email                : kumber@tiscalinet.it
 ***************************************************************************/

/***************************************************************************
 *                                                                                                                 
 *   This program is free software; you can redistribute it and/or modify  
 *   it under the terms of the GNU General Public License, Version 2,        
 *   as published by the Free Software Foundation.                                  
 *                                                                                                                 
 ***************************************************************************/

#include "defs.h"
#include "../../common/data/mem_data_chunk.h"
#include "../abstract_codec_parameters.h"
#include "../../common/serializable.h"

#ifndef DESCRIPTOR_H_
#define DESCRIPTOR_H_

/**
 * A Descriptor is the littlest independent MDC unit.
 * It represents a piece of MDC stream.
 */
class Descriptor : public Serializable
{
private:
	string m_complete_stream_md5_hash;
	Uint8 m_flow_id;
	Uint32 m_sequence_number;
	//string m_codec_name;
	Uint8 m_codec_code;
	AbstractCodecParameters* m_codec_parameters;
	MemDataChunk m_payload;
public:
	Descriptor();
	~Descriptor();
	
	/*
	 * Get codec parameter's size.
	 * @returns: codec parameters' size
	 */
	Uint32 get_codec_parameters_size() const;
	
	/*
	 * Get flow identifier.
	 * @returns: flow identifier of a stream
	 */
	Uint8 get_flow_id() const;
	
	/*
	 * Set flow identifier.
	 * @id: flow identifier
	 */
	void set_flow_id(Uint8 id);
	
	/*
	 * Get sequence number.
	 * @returns: sequence number
	 */
	Uint32 get_sequence_number() const;
	
	/*
	 * Set sequence number.
	 * @seq_num: sequence number
	 */
	void set_sequence_number(Uint32 seq_num);
	
	/*
	 * Set codec name.
	 * @codec_name: codec name
	 */
	void set_codec_name(const string& codec_name);
	
	/*
	 * Get codec name.
	 * @returns: codec name
	 */
	string get_codec_name() const;
	
	/*
	 * Get codec parameters.
	 * @returns: codec parameters
	 */
	AbstractCodecParameters* get_codec_parameter() const;
	
	/*
	 * Set codec parameters.
	 * @acp: abstract codec parameters
	 */
	void set_codec_parameter(AbstractCodecParameters* acp);
	
	/*
	 * Get payload size.
	 * @returns: payload size
	 */
	Uint16 get_payload_size() const;
	
	/*
	 * Set payload.
	 * @payload: real payload
	 */
	void set_payload(MemDataChunk& payload);
	
	/*
	 * Get payload.
	 * @returns: data chunk containing payload
	 */
	MemDataChunk* get_payload() const;
	
	/**
	 * This function serializes the Descriptor state and produces a DataChunk for net sending.
	 * It is the opposite of deserialize() function.
	 */
	MemDataChunk& serialize() const;
	
	/**
	 * This function deserializes data, i.e. restore Descriptor state embedded in data.
	 * It is the opposite of serialize();
	 */
	bool deserialize(const IDataChunk* data);
	
	string get_stream_id() const;
	
	void set_stream_id(string stream_id);
	
	
};

#endif /*DESCRIPTOR_H_*/
