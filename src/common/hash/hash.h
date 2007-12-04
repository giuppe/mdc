

#ifndef HASH_H_
#define HASH_H_

#include "defs.h"
#include <string>
#include "../data_chunk.h"

class Hash
{
public:
	static std::string md5_from_file(std::string path);
	
	static std::string md5_from_string(std::string str);
	
	static std::string md5_from_datachunk(const DataChunk& data);
	
};

#endif /*HASH_H_*/
