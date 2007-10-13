/***************************************************************************
                          AbstractStream.h  -  Stream abstract class
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
	 * Get data stream from disk.
	 * @init_position: read from this initial position
	 * @dinal_position: read to this final position
	 * @returns: data between positions
	 */
	virtual char get_data(Uint32 init_position, Uint32 final_position) const = 0;
	
	/*
	 * Get data dimension from file.
	 * @returns: dimension
	 */
	virtual Uint32 get_data_dim () const = 0;
	
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
	virtual std::string& get_stream_name() const = 0;
	
	/*
	 * Set payload size.
	 * @size: size to be set
	 */
	virtual void set_payload_size(Uint32 size) const = 0;
	
	/*
	 * Get payload size.
	 * @returns: size
	 */
	virtual	Uint32 get_payload_size() = 0;
	
	/*
	 * Set position in file.
	 * @new_position: position to be considered as new current position
	 */
	virtual void set_current_position(Uint32 new_position) = 0;
	
	/*
	 * Get current position in file.
	 * @returns: current position
	 */
	virtual Uint32 get_current_position() = 0;
	
	/*
	 * Get hash based on a stream.
	 * @returns: hash string
	 */
	virtual std::string& get_stream_hash() = 0;
	
	/*
	 * Update hash based on current data.
	 */
	virtual void update_stream_hash() = 0; //update
};

#endif /*ABSTRACTSTREAM_H_*/
