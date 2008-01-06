/***************************************************************************
                          data_chunk.h  -  DataChunk class
                             -------------------
    begin                : Jul 13 2007
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



#ifndef MEM_DATA_CHUNK_H_
#define MEM_DATA_CHUNK_H_

#include "defs.h"
#include "abstract_data_chunk.h"

/**
 * Represents a stream of bytes in memory.
 */
class MemDataChunk : public AbstractDataChunk
{

	//friend class NetManager;

protected:
	
	Uint8* m_data;
	
	Uint8* m_real_data;
	
	Uint32 m_lenght;
	
	//bool m_initialized;
	
	MemDataChunk(const MemDataChunk&){};
	
	MemDataChunk(MemDataChunk&){};
	
	void set_content(Uint8* data, Uint32 lenght);
	
	bool get_data(Uint32 offset, Uint32 lenght, Uint8* data) const;
	
	bool find_null(Uint32 offset, Uint32& position) const;
	
public:
	
	/**
	 * Default DataChunk constructor.
	 */
	MemDataChunk():m_lenght(0){};
	
	~MemDataChunk();
	

	
	/**
	 * @returns the inner data stream, as a pointer to "char"s
	 */
	Uint8* get_data() const;
	
	/**
	 * @returns the total steam lenght.
	 */
	Uint32 get_lenght() const;
	
	/**
	 * Used to append a DataChunk at the end of the stream.
	 */
//	void operator+=(const MemDataChunk& data);

	/**
	 * Extracts 32 bits from the beginning of the stream, 
	 * converting them to a 32 bit unsigned integer.
	 * @param data the data extracted.
	 * @returns true if the data is valid.
	 */ 
	bool extract_head(Uint32& data);
	
	/**
	 * Extracts 32 bits from the beginning of the stream, 
	 * converting them to a 32 bit signed integer.
	 * @param data the data extracted.
	 * @returns true if the data is valid.
	 */ 
	bool extract_head(Sint32& data);
	
	/**
	 * Extracts 16 bits from the beginning of the stream, 
	 * converting them to a 16 bit unsigned integer.
	 * @param data the data extracted.
	 * @returns true if the data is valid.
	 */ 
	bool extract_head(Uint16& data);
	
	/**
	 * Extracts 16 bits from the beginning of the stream, 
	 * converting them to a 16 bit signed integer.
	 * @param data the data extracted.
	 * @returns true if the data is valid.
	 */ 
	bool extract_head(Sint16& data);
	
	/**
	 * Extracts 8 bits from the beginning of the stream, 
	 * converting them to a 8 bit unsigned integer.
	 * @param data the data extracted.
	 * @returns true if the data is valid.
	 */ 
	bool extract_head(Uint8& data);
	
	/**
	 * Extracts 8 bits from the beginning of the stream, 
	 * converting them to a 8 bit signed integer.
	 * @param data the data extracted.
	 * @returns true if the data is valid.
	 */ 
	bool extract_head(Sint8& data);
	
	/**
	 * Extracts a null-terminated string from the beginning of the stream, 
	 * converting it to a c-string.
	 * @param data the data extracted.
	 * @returns true if the data is valid.
	 */ 
	bool extract_head(char* &data);
	
	
	void append_data(Uint32 lenght, Uint8* data);
	
	bool extract_head(Uint32 lenght, Uint8* &data);
	
	bool extract_head(Uint32 lenght, MemDataChunk &data);
	
	void erase();
	
	const char* compute_hash_md5() const;
	
};

#endif /*MEM_DATA_CHUNK_H_*/
