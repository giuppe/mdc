
#ifndef FILE_DATA_CHUNK_H_
#define FILE_DATA_CHUNK_H_

#include "defs.h"
#include "abstract_data_chunk.h"

class FileDataChunk : public AbstractDataChunk
{
protected:
	FILE* m_file;
	string m_path;
	
	bool m_is_null;
	
	bool m_is_open_file;
	
	void open_file();
	
	bool get_data(Uint32 offset, Uint32 lenght, Uint8*& data) const;
	
public:
	FileDataChunk():m_is_null(true),m_is_open_file(false){}
	
	explicit FileDataChunk(string path);
	
	~FileDataChunk();
	
	
		/**
		 * @returns the total steam lenght.
		 */
	Uint32 get_lenght() const;
		
		
	void append_data(Uint32 lenght, Uint8* data);
		
	void erase();
			
	const char* compute_hash_md5() const;
		
	
};


#endif /*FILE_DATA_CHUNK_H_*/
