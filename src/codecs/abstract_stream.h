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
	 * @path: filesystem path of file to load;
	 * @returns: true if operation is successful
	 */
	virtual bool load_from_disk(const std::string& path) = 0;
	
	
	/*
	 * Saves a stream to disk.
	 * @path: filesystem path of file to save;
	 * @returns: true if operation is successful
	 */
	virtual bool save_to_disk(const std::string& path) = 0;
};

#endif /*ABSTRACTSTREAM_H_*/
