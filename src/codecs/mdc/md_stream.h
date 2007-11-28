/***************************************************************************
                          md_stream.h  -  Multiple Descriptor Stream class
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

#include <SDL/SDL.h>
#include <string>
#include <vector>
#include "../../common/serializable.h"
#include "../../common/data_chunk.h"

#ifndef MDSTREAM_H_
#define MDSTREAM_H_

class Descriptor;
class MDStream : public Serializable
{
private:
	std::vector<std::vector<Descriptor*> > m_stream;
	std::vector<std::vector<bool> > m_valid_descriptor;
	void set_descriptor(Uint8 flow, Uint32 sequence, Descriptor* descriptor);
	std::string m_name;
	std::string m_hash;
	bool m_is_empty;
	bool m_is_inited;
	//Uint32 m_valid_descriptors_number;
public:
	MDStream();
	
	/*
	 * Initialize MDStream.
	 * @n_flows: flows number in wich the file must be divided;
	 * @sequence_size: size of each sequence
	 */
	void init(Uint8 n_flows, Uint32 sequence_size);
	
	MDStream(Uint8 n_flows, Uint32 sequence_size);
	~MDStream();
	
	/*
	 * Gets the descriptor. Returns true if valid.
	 * @flow: Flow identifier;
	 * @sequence: sequence number of the descriptor in the flow
	 * @descriptor: return value
	 */
	bool get_descriptor(Uint8 flow, Uint32 sequence, Descriptor* &descriptor) const;
	
	/*
	 * Sets the descriptor.
	 * @descriptor: descriptor to be set
	 */
	void set_descriptor(Descriptor* descriptor);
	
	/*
	 * Loads a stream from disk.
	 * @path: filesystem path of file to load;
	 * @returns: true if operation is successful
	 */
	bool load_from_disk(const std::string& path);
	
	/*
	 * Saves a stream to disk.
	 * @path: filesystem path of file to save;
	 * @returns: true if operation is successful
	 */
	bool save_to_disk(const std::string& path);
	
	/*
	 * Gets a stream name.
	 * @returns: stream name
	 */
	std::string get_name() const;
	
	/*
	 * Gets a stream name.
	 * @returns: stream hash
	 */	
	std::string get_hash() const;
	
	/*
	 * Verifies if a stream is empty.
	 * @returns: true if stream is empty
	 */
	bool is_empty() const;
	DataChunk& serialize() const;
	void deserialize(const DataChunk&);
	
	/*
	 * Gets maximum sequences number
	 * @returns: sequences number
	 */
	Uint32 get_sequences_number() const;
	
	/*
	 * Gets flows' number
	 * @returns: flows' number
	 */
	Uint8 get_flows_number() const;
	
	bool is_valid(Uint8 flow, Uint32 sequence) const;
	
	/*
	 * Gets the valid descriptors number
	 * @returns: valid descriptors number
	 */
	//Uint32 get_valid_descriptors_number() const;
};

#endif /*MDSTREAM_H_*/