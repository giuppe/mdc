/***************************************************************************
                          serializable.h  -  Insert description
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

#include "defs.h"
#include "data_chunk.h"

#ifndef SERIALIZABLE_H_
#define SERIALIZABLE_H_

/**
 * Interface for serializable (e.g. encodable) objects.
 * It permits to obtain an object representation in form of DataChunks.
 */
class Serializable
{
public:
	
	/**
			 * This function serializes the object's state and produces a DataChunk.
			 * It is the opposite of deserialize() function.
			 */
	virtual DataChunk& serialize() const = 0;
	
	/**
		 * This function deserializes data, i.e. restore object's state embedded in data.
		 * It is the opposite of serialize().
		 */
	virtual void deserialize(const DataChunk&) = 0;
	
	virtual ~Serializable(){};

};

#endif /*SERIALIZABLE_H_*/
