/***************************************************************************
           		   pixel_container.h  - Pixel management class
                             -------------------
    begin                : Dec 14, 2007
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



#ifndef PIXEL_CONTAINER_H_
#define PIXEL_CONTAINER_H_

#include "defs.h"
#include "../../common/serializable.h"

class pixel_container : public Serializable{
private:
	Uint8 m_r, m_g, m_b;
public:
	pixel_container();
	~pixel_container();
	
	/*
	 * Sets pixel red color component.
	 * @red: red color component
	 */
	void set_r(Uint8 red);
	
	/*
	 * Sets pixel green color component.
	 * @green: green color component
	 */	
	void set_g(Uint8 green);
	
	/*
	 * Sets pixel blue color component.
	 * @blue: blue color component
	 */
	void set_b(Uint8 blue);
	
	/*
	 * Gets pixel red color component.
	 * @returns: red color component
	 */
	Uint8 get_r() const;
	
	/*
	 * Gets pixel green color component.
	 * @returns: green color component
	 */
	Uint8 get_g() const;
	
	/*
	 * Gets pixel blue color component.
	 * @returns: blue color component
	 */
	Uint8 get_b() const;
	
	/*
	 * Serialize a pixel container into a DataChunk.
	 * @returns: DataChunk serialized
	 */
	MemDataChunk& serialize() const;
	
	
	/*
	 * Deserialize a DataChunk into a pixel container.
	 * @IDataChunk: DataChunk to be deserialized
	 * @returns: true if operation successfull
	 */
	bool deserialize(const IDataChunk*);
};

#endif /*PIXEL_CONTAINER_H_*/
