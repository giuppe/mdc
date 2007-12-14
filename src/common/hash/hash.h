

#ifndef HASH_H_
#define HASH_H_

#include "defs.h"

#include "../data/mem_data_chunk.h"

class Hash
{
public:
	static string md5_from_file(string path);
	
	static string md5_from_string(string str);
	
	static string md5_from_datachunk(const MemDataChunk& data);
	
};

#endif /*HASH_H_*/
