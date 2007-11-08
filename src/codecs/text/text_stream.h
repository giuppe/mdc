/***************************************************************************
                       text_stream.h  -  Text Stream class
                             -------------------
    begin                : Jul 13, 2007
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

#include <cstdlib>
#include <cstdio>
#include "../descriptor.h"
#include "../abstract_stream.h"
#include <vector>
#include <string>
#include "../../common/data_chunk.h"

#ifndef TEXT_STREAM_H_
#define TEXT_STREAM_H_

class TextStream : public AbstractStream
{
private:
	std::vector<char> m_data;
	std::string m_stream_name;
	Uint32 m_last_current_position;
	std::string m_hash;
public:	
	TextStream();

	/*
	 * Loads a stream from disk.
	 * @path: filesystem path of file to load;
	 * @returns: true if operation is successful
	 */
	bool load_from_disk(const std::string& path);
	
	/*
	 * Get a data set from a file.
	 * @dimension: number of single data
	 * @returns: a data chunk containing data set
	 */
	DataChunk& get_data(Uint16 dimension);
	
	/*
	 * Get data dimension.
	 * @returns: data set dimension
	 */
	Uint32 get_data_dim() const;
	
	/*
	 * Set stream name.
	 * @name: stream name
	 */
	void set_stream_name(std::string& name);
	
	/*
	 * Get stream name.
	 * @returns: stream name
	 */
	std::string get_stream_name() const;
	
	/*
	 * Get cursor's last position in stream.
	 * @returns: last position
	 */
	Uint32 get_last_current_position() const;
	
	/*
	 * Get stream hash.
	 * @returns: hash code calculated on stream content
	 */
	std::string get_stream_hash() const;
	
	/*
	 * Update stream hash.
	 */
	void update_stream_hash();
	
	/*
	 * Saves a stream to disk.
	 * @path: filesystem path of file to save;
	 * @returns: true if operation is successful
	 */
	bool save_to_disk(const std::string& path);
	~TextStream();
};

#endif /*TEXT_STREAM_H_*/