

#ifndef HASH_H_
#define HASH_H_

#include "defs.h"

#include "../data_chunk.h"

class Hash
{
public:
	static string md5_from_file(string path);
	
	static string md5_from_string(string str);
	
	static string md5_from_datachunk(const DataChunk& data);
	
};

#endif /*HASH_H_*/
