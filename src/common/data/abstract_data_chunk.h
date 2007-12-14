
#ifndef ABSTRACT_DATA_CHUNK_H_
#define ABSTRACT_DATA_CHUNK_H_

#include "defs.h"
#include "i_data_chunk.h"

class AbstractDataChunk : public IDataChunk
{
public:
		AbstractDataChunk(){}
		
		DataChunkIterator get_iterator() const;
		
		void operator+=(const IDataChunk* data);
		
		/**
		 * Adds a 32 bit long unsigned integer (i.e. "unsigned int" on i386)  to the end of the stream.
		 * @param data the integer to add.
		 */
		void append_Uint32(Uint32 data);
		
		/**
			 * Add a 32 bit long signed integer (i.e. "int" on i386)  to the end of the stream.
			 * @param data the integer to add.
			 */
		void append_Sint32(Sint32 data);
		
		/**
			 * Add a 16 bit long unsigned integer (i.e. "unsigned short" on i386) to the end of the stream.
			 * @param data the integer to add.
			 */
		void append_Uint16(Uint16 data);
		
		/**
			 * Add a 16 bit long signed integer (i.e. "short" on i386)  to the end of the stream.
			 * @param data the integer to add.
			 */
		void append_Sint16(Sint16 data);
		
		/**
			 * Add an 8 bit long unsigned integer (i.e. "unsigned char" on i386)  to the end of the stream.
			 * @param data the integer to add.
			 */
		void append_Uint8(Uint8 data);
		
		/**
			 * Add an 8 bit long signed integer (i.e. "char" on i386)  to the end of the stream.
			 * @param data the integer to add.
			 */
		void append_Sint8(Sint8 data);
		
		/**
			 * Add a c-string (i.e. null-terminated string) to the end of the stream.
			 * @param data the string to add.
			 */
		void append_cstring(const char* data);

		
};

#endif /*ABSTRACT_DATA_CHUNK_H_*/
