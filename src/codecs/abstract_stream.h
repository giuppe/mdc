/***************************************************************************
                          abstract_stream.h  -  Stream abstract class
                             -------------------
    begin                : Jul 13, 2007
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

#include <string>
#include <vector>
#include "../common/data_chunk.h"

#ifndef ABSTRACTSTREAM_H_
#define ABSTRACTSTREAM_H_

class AbstractStream
{
public:
	virtual ~AbstractStream(){};

	/*
	 * Loads a stream from disk.
	 * @path: filesystem path of file to load
	 * @returns: true if operation is successful
	 */
	virtual bool load_from_disk(const std::string& path) = 0;
	
	/*
	 * Saves a stream to disk.
	 * @path: filesystem path of file to save;
	 * @returns: true if operation is successful
	 */
	virtual bool save_to_disk(const std::string& path) = 0;

	/*
	 * Get data from memory.
	 * @dimension: quantity of data to be selected
	 * @returns: data chunk containing data from current position to new current position
	 */
	virtual DataChunk& get_data(Uint16 dimension) = 0;
	
	/*
	 * Get data dimension from file.
	 * @returns: dimension
	 */
	virtual Uint32 get_data_dim() const = 0;
	
	/*
	 * Set stream name.
	 * @name: name to be set
	 */
	virtual void set_stream_name(std::string& name) = 0;
	
	/*
	 * Get stream name.
	 * @init_position: read from this initial position
	 * @final_position: read to this final position
	 * @returns: name
	 */
	virtual std::string get_stream_name() const = 0;
	
	/*
	 * Get last current position in file.
	 * @returns: last current position
	 */
	virtual Uint32 get_last_current_position() const = 0;
	
	/*
	 * Get stream hash.
	 * @returns: hash string
	 */
	virtual std::string get_stream_hash() const = 0;
	
	/*
	 * Update hash based on file content.
	 */
	virtual void update_stream_hash() = 0;
	
	/*
	 * Insert data to the current stream.
	 * @data: data to be added;
	 */
	virtual void set_data(DataChunk& data) = 0;
};

#endif /*ABSTRACTSTREAM_H_*/
