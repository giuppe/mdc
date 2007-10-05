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
#include "string.h"

#ifndef TEXT_STREAM_H_
#define TEXT_STREAM_H_

class TextStream {
private:
	char* character;
public:
	/*
	 * Loads a stream from disk.
	 * @path: filesystem path of file to load;
	 * @returns: true if operation is successful
	 */
	bool load_from_disk(const std::string& path);
	char& get_character ();
	
	/*
	 * Saves a stream to disk.
	 * @path: filesystem path of file to save;
	 * @returns: true if operation is successful
	 */
	virtual bool save_to_disk(const std::string& path) = 0;
	~TextStream(){};
};

#endif /*TEXT_STREAM_H_*/
