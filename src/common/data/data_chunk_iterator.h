
#ifndef DATA_CHUNK_ITERATOR_H_
#define DATA_CHUNK_ITERATOR_H_

#include "../defs.h"

class IDataChunk;

class DataChunkIterator
{
private:
	Uint32 m_position;
	const IDataChunk* m_data;
	
	bool m_is_null;
	
public:
	DataChunkIterator():m_is_null(true){};
	
	DataChunkIterator(const IDataChunk* data):m_position(0),m_data(data),m_is_null(false){}
	
	bool is_null() const {return m_is_null;}
	
	void seek_at(Uint32 byte_pos){m_position=byte_pos;};
	
	/**
		 * Extracts 32 bits from the beginning of the stream, 
		 * converting them to a 32 bit unsigned integer.
		 * @param data the data extracted.
		 * @returns true if the data is valid.
		 */ 
		bool get_Uint32(Uint32& data);
		
		/**
		 * Extracts 32 bits from the beginning of the stream, 
		 * converting them to a 32 bit signed integer.
		 * @param data the data extracted.
		 * @returns true if the data is valid.
		 */ 
		bool get_Sint32(Sint32& data);
		
		/**
		 * Extracts 16 bits from the beginning of the stream, 
		 * converting them to a 16 bit unsigned integer.
		 * @param data the data extracted.
		 * @returns true if the data is valid.
		 */ 
		bool get_Uint16(Uint16& data);
		
		/**
		 * Extracts 16 bits from the beginning of the stream, 
		 * converting them to a 16 bit signed integer.
		 * @param data the data extracted.
		 * @returns true if the data is valid.
		 */ 
		bool get_Sint16(Sint16& data);
		
		/**
		 * Extracts 8 bits from the beginning of the stream, 
		 * converting them to a 8 bit unsigned integer.
		 * @param data the data extracted.
		 * @returns true if the data is valid.
		 */ 
		bool get_Uint8(Uint8& data);
		
		/**
		 * Extracts 8 bits from the beginning of the stream, 
		 * converting them to a 8 bit signed integer.
		 * @param data the data extracted.
		 * @returns true if the data is valid.
		 */ 
		bool get_Sint8(Sint8& data);
		
		/**
		 * Extracts a null-terminated string from the beginning of the stream, 
		 * converting it to a c-string.
		 * @param data the data extracted.
		 * @returns true if the data is valid.
		 */ 
		bool get_cstring(char* &data);
		
		
		bool get_data(Uint32 lenght, Uint8* &data);
		
		bool get_data_chunk(Uint32 lenght, IDataChunk* data);
};

#endif /*DATA_CHUNK_ITERATOR_H_*/
