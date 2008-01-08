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

#include "../abstract_stream.h"


#include "../../common/data/mem_data_chunk.h"

#ifndef TEXT_STREAM_H_
#define TEXT_STREAM_H_

class TextStream : public AbstractStream
{
private:
	vector<char> m_data;
	string m_stream_name;
	string m_hash;
public:	
	TextStream();

	/*
	 * Get a data set from a file.
	 * @dimension: number of single data
	 * @returns: a data chunk containing data set
	 */
	MemDataChunk& get_data(Uint16 dimension) const;

	/*
	 * Get parts of a text stream, specifying size and starting from offset.
	 * @param offset: starting point
	 * @param size: data size
	 * @returns: a data chunk containing data selected
	 */
	MemDataChunk& get_data(Uint64 offset, Uint64 size) const;

	/*
	 * Get data dimension.
	 * @returns: data set dimension
	 */
	Uint32 get_data_dim() const;

	/*
	 * Set stream name.
	 * @name: stream name
	 */
	void set_stream_name(string& name);

	/*
	 * Get stream name.
	 * @returns: stream name
	 */
	string get_stream_name() const;

	/*
	 * Get stream hash.
	 * @returns: hash code calculated on stream content
	 */
	string compute_hash_md5() const;


	/*
	 * Saves a stream to disk.
	 * @path: filesystem path of file to save;
	 * @returns: true if operation is successful
	 */
	bool save_to_disk(const string& path) const;

	/*
	 * Insert data to the current stream.
	 * @data: data to be added;
	 */
	void set_data(const MemDataChunk& data);
	
	
	
	~TextStream();
	
	
	/*
	 * Loadss a stream from disk.
	 * @path: filesystem path of file to load;
	 * @returns: true if operation is successful
	 */
	bool load_from_disk(const string& path);
	
	
	MemDataChunk& serialize() const;
	
	
	
	bool deserialize(const IDataChunk*);
	
	
};

#endif /*TEXT_STREAM_H_*/
