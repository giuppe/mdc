
#ifndef I_DATA_CHUNK_H_
#define I_DATA_CHUNK_H_

#include "defs.h"
#include "data_chunk_iterator.h"

class IDataChunk
{
protected:
	friend class DataChunkIterator;
	virtual bool get_data(Uint32 offset, Uint32 lenght, Uint8* data) const =0;
	
	virtual bool find_null(Uint32 offset, Uint32& position) const = 0;
public:
	virtual ~IDataChunk(){}
	

	
	virtual DataChunkIterator get_iterator() const =0;
	/**
	 * @returns the total steam lenght.
	 */
	virtual Uint32 get_lenght() const=0;
	
	/**
	 * Used to append a DataChunk at the end of the stream.
	 */
	virtual void operator+=(const IDataChunk* data)=0;
	
	/**
	 * Adds a 32 bit long unsigned integer (i.e. "unsigned int" on i386)  to the end of the stream.
	 * @param data the integer to add.
	 */
	virtual void append_Uint32(Uint32 data)=0;
	
	/**
		 * Add a 32 bit long signed integer (i.e. "int" on i386)  to the end of the stream.
		 * @param data the integer to add.
		 */
	virtual void append_Sint32(Sint32 data)=0;
	
	/**
		 * Add a 16 bit long unsigned integer (i.e. "unsigned short" on i386) to the end of the stream.
		 * @param data the integer to add.
		 */
	virtual void append_Uint16(Uint16 data)=0;
	
	/**
		 * Add a 16 bit long signed integer (i.e. "short" on i386)  to the end of the stream.
		 * @param data the integer to add.
		 */
	virtual void append_Sint16(Sint16 data)=0;
	
	/**
		 * Add an 8 bit long unsigned integer (i.e. "unsigned char" on i386)  to the end of the stream.
		 * @param data the integer to add.
		 */
	virtual void append_Uint8(Uint8 data)=0;
	
	/**
		 * Add an 8 bit long signed integer (i.e. "char" on i386)  to the end of the stream.
		 * @param data the integer to add.
		 */
	virtual void append_Sint8(Sint8 data)=0;
	
	/**
		 * Add a c-string (i.e. null-terminated string) to the end of the stream.
		 * @param data the string to add.
		 */
	virtual void append_cstring(const char* data)=0;
	
	virtual void append_data(Uint32 lenght, Uint8* data)=0;
	
	virtual void erase()=0;
		
	virtual const char* compute_hash_md5() const=0;
	
};

#endif /*I_DATA_CHUNK_H_*/
