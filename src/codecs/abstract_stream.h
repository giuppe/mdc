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



#include "../common/data/mem_data_chunk.h"
#include "../common/serializable.h"

#ifndef ABSTRACTSTREAM_H_
#define ABSTRACTSTREAM_H_

class AbstractStream : public Serializable
{
public:
	virtual ~AbstractStream(){};

	/*
	 * Loads a stream from disk.
	 * @path: filesystem path of file to load
	 * @returns: true if operation is successful
	 */
	virtual bool load_from_disk(const string& path) = 0;
	
	/*
	 * Saves a stream to disk.
	 * @path: filesystem path of file to save;
	 * @returns: true if operation is successful
	 */
	virtual bool save_to_disk(const string& path) const = 0;
	
	
	/*
	 * Get data dimension from file.
	 * @returns: dimension
	 */
	virtual Uint32 get_data_dim() const = 0;
	
	/*
	 * Set stream name.
	 * @name: name to be set
	 */
	virtual void set_stream_name(string& name) = 0;
	
	/*
	 * Get stream name.
	 * @init_position: read from this initial position
	 * @final_position: read to this final position
	 * @returns: name
	 */
	virtual string get_stream_name() const = 0;
	
	/*
	 * Get stream hash.
	 * @returns: hash string
	 */
	virtual string compute_hash_md5() const = 0;
	

	
	/*
	 * Insert data to the current stream.
	 * @data: data to be added;
	 */
	virtual void set_data(const MemDataChunk& data) = 0;
	
	/*
	 * Gets data from a file.
	 * @offset: initial position;
	 * @size: data quantity taken;
	 * @returns: a DataChunk containing the data readed.
	 */
	virtual MemDataChunk& get_data(Uint64 offset, Uint64 size) const = 0;
};

#endif /*ABSTRACTSTREAM_H_*/
