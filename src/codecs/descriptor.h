/***************************************************************************
                          descriptor.h  -  MDC Descriptor class
                             -------------------
    begin                : Jul 13 2007
    copyright          : (C) 2007 by Giuseppe D'Aqui', Livio Pipitone
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
	AbstractCodecParameters* codec_parameter;
	Uint32 m_payload_size;
	Uint8* m_payload;
public:
	Descriptor() {};

	Uint8 get_flow_id() const;
	
	void set_flow_id(Uint8 id);
	
	Uint32 get_sequence_number() const;

	void set_sequence_number(Uint32 seq_num);
	
	std::string get_file_name() const;

	void set_file_name(const std::string& file_name);
	
	std::string get_hash() const;
	
	void set_hash(const std::string& hash);

	void set_codec_name(const std::string& codec_name);

	std::string get_codec_name() const;
	
	AbstractCodecParameters* get_codec_parameter () const;
	
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
