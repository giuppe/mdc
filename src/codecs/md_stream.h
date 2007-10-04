/***************************************************************************
                          MDStream.h  -  Multiple Descriptor Stream class
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


#ifndef MDSTREAM_H_
#define MDSTREAM_H_

class Descriptor;

class MDStream
{
	
private:
	
	std::vector<std::vector<Descriptor*> > m_stream;
	
	std::vector<std::vector<bool> > m_valid_descriptor;
	
	void set_descriptor(Uint8 flow, Uint32 sequence, Descriptor* descriptor);
	
	std::string m_name;
	
	std::string m_hash;
	
	bool m_is_empty;
	
	bool m_is_inited;
	
	void init(Uint8 n_flows, Uint32 sequence_size);
	
public:
	
	MDStream();
	
	MDStream(Uint8 n_flows, Uint32 sequence_size);
	
	~MDStream();
	
	/*
	 * Gets the descriptor. Returns true if valid.
	 * @flow: Flow identifier;
	 * @sequence: sequence number of the descriptor in the flow
	 * @descriptor: return value
	 */
	bool get_descriptor(Uint8 flow, Uint32 sequence, Descriptor* &descriptor) const;
	
	
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
	
	
	
	std::string get_name() const;
	
	
	std::string get_hash() const;
	
	bool is_empty(){return m_is_empty;}
	
};

#endif /*MDSTREAM_H_*/
