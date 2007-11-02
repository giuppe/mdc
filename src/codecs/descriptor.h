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
#include "../common/data_chunk.h"
#include "abstract_codec_parameters.h"
#include "../common/serializable.h"

#ifndef DESCRIPTOR_H_
#define DESCRIPTOR_H_

/**
 * A Descriptor is the littlest independent MDC unit.
 * It represents a piece of MDC stream.
 */
class Descriptor : public Serializable
{
private:
	Uint8 m_flow_id;
	Uint32 m_sequence_number;
	std::string m_file_name;
	std::string m_hash;
	std::string m_codec_name;
	Uint32 m_codec_parameters_size;
	AbstractCodecParameters* m_codec_parameters;
	Uint32 m_payload_size;
	Uint8* m_payload;
public:
	Descriptor() {};
	~Descriptor();
	
	/*
	 * Get codec parameter's size.
	 * @returns: codec parameters' size
	 */
	Uint32 get_codec_parameters_size();
	
	/*
	 * Set codec parameters' size.
	 * @size: size of codec parameters
	 */
	void set_codec_parameters_size(Uint32 size);
	
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
	 * Get file name.
	 * @returns: file name
	 */
	std::string get_file_name() const;
	
	/*
	 * Set file name.
	 * @file_name: file name
	 */
	void set_file_name(const std::string& file_name);
	
	/*
	 * Get hash.
	 * @returns: hash code
	 */
	std::string get_hash() const;
	
	/*
	 * Set hash.
	 * @hash: hash code
	 */
	void set_hash(const std::string& hash);
	
	/*
	 * Set codec name.
	 * @codec_name: codec name
	 */
	void set_codec_name(const std::string& codec_name);
	
	/*
	 * Get codec name.
	 * @returns: codec name
	 */
	std::string get_codec_name() const;
	
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
	 * Set payload size.
	 * @psize: payload size
	 */
	void set_payload_size(Uint32 psize);
	
	/*
	 * Get payload size.
	 * @returns: payload size
	 */
	Uint32 get_payload_size();
	
	/*
	 * Set payload.
	 * @payload: real payload
	 */
	void set_payload(DataChunk& payload);
	
	/*
	 * Get payload.
	 * @returns: data chunk containing payload
	 */
	DataChunk* get_payload();
	
	/**
	 * This function serializes the Descriptor state and produces a DataChunk for net sending.
	 * It is the opposite of deserialize() function.
	 */
	DataChunk& serialize() const;
	
	/**
	 * This function deserializes data, i.e. restore Descriptor state embedded in data.
	 * It is the opposite of serialize();
	 */
	void deserialize(const DataChunk& data);
};

#endif /*DESCRIPTOR_H_*/
