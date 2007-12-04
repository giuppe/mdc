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

#include "defs.h"

#ifndef DATA_CHUNK_H_
#define DATA_CHUNK_H_

/**
 * Represents a stream of bytes.
 */
class DataChunk
{

	friend class NetManager;

private:
	
	Uint8* m_data;
	
	Uint8* m_real_data;
	
	Uint32 m_lenght;
	
	//bool m_initialized;
	
	DataChunk(const DataChunk&){};
	
	DataChunk(DataChunk&){};
	

	
	void set_content(Uint8* data, Uint32 lenght);
	
	
public:
	
	/**
	 * Default DataChunk constructor.
	 */
	DataChunk():m_lenght(0){};
	
	~DataChunk();
	
	
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
	void operator+=(const DataChunk& data);
	
	/**
	 * Adds a 32 bit long unsigned integer (i.e. "unsigned int" on i386)  to the end of the stream.
	 * @param data the integer to add.
	 */
	void append(Uint32 data);
	
	/**
		 * Add a 32 bit long signed integer (i.e. "int" on i386)  to the end of the stream.
		 * @param data the integer to add.
		 */
	void append(Sint32 data);
	
	/**
		 * Add a 16 bit long unsigned integer (i.e. "unsigned short" on i386) to the end of the stream.
		 * @param data the integer to add.
		 */
	void append(Uint16 data);
	
	/**
		 * Add a 16 bit long signed integer (i.e. "short" on i386)  to the end of the stream.
		 * @param data the integer to add.
		 */
	void append(Sint16 data);
	
	/**
		 * Add an 8 bit long unsigned integer (i.e. "unsigned char" on i386)  to the end of the stream.
		 * @param data the integer to add.
		 */
	void append(Uint8 data);
	
	/**
		 * Add an 8 bit long signed integer (i.e. "char" on i386)  to the end of the stream.
		 * @param data the integer to add.
		 */
	void append(Sint8 data);
	
	/**
		 * Add a c-string (i.e. null-terminated string) to the end of the stream.
		 * @param data the string to add.
		 */
	void append(const char* data);
	
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
	
	
	void append(Uint32 lenght, Uint8* data);
	
	bool extract_head(Uint32 lenght, Uint8* &data);
	
	bool extract_head(Uint32 lenght, DataChunk &data);
	
	void erase();
	
	const char* compute_hash_md5() const;
	
};

#endif /*DATA_CHUNK_H_*/
