/***************************************************************************
                          TextStream.h  -  Text Stream class
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

#include "stdlib.h"
#include "stdio.h"
#include "descriptor.h"
#include "abstract_stream.h"
#include "vector.h"
#include "string.h"
#include "../sha/mhash.h"

#ifndef TEXT_STREAM_H_
#define TEXT_STREAM_H_

class TextStream : public AbstractStream
{
private:
	vector<char> m_characters;
	std::string m_stream_name;
	Uint32 m_size;
	Uint32 m_current_position;
	MHASH m_td;
	std::string m_hash;
public:
	/*
	 * Loads a stream from disk.
	 * @path: filesystem path of file to load;
	 * @returns: true if operation is successful
	 */
	bool load_from_disk(const std::string& path);
	char get_characters(Uint32 init_position, Uint32 final_position) const;
	Uint32 get_characters_dim () const;
	void set_stream_name(std::string& name);
	std::string& get_stream_name() const;
	void set_payload_size(Uint32 size) const;
	Uint32 get_payload_size();
	void set_current_position(Uint32 new_position);
	Uint32 get_current_position();
	std::string& get_stream_hash();
	void set_stream_hash();
	
	/*
	 * Saves a stream to disk.
	 * @path: filesystem path of file to save;
	 * @returns: true if operation is successful
	 */
	bool save_to_disk(const std::string& path);
	~TextStream(){};
};

#endif /*TEXT_STREAM_H_*/
