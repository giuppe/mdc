
#include "defs.h"
#include "hash.h"
#include "hashlibpp/hl_hashwrapper.h"
#include "hashlibpp/hl_md5wrapper.h"


std::string Hash::md5_from_file(std::string path)
{
	/*
	 * creating a wrapper object
	 */
	hashwrapper *myWrapper = new md5wrapper();
	

	
	/*
	 * create a hash based on a file
	 */
	std::string hash2 = myWrapper->getHashFromFile(path);
	
	delete myWrapper;
	
	return hash2;
}

std::string Hash::md5_from_string(std::string str)
{
	/*
	 * creating a wrapper object
	 */
	hashwrapper *myWrapper = new md5wrapper();
	

	
/*
 * create a hash from a string
 */
std::string hash1 = myWrapper->getHashFromString(str);
delete myWrapper;

return hash1;
}

std::string Hash::md5_from_datachunk(const DataChunk& data)
{
	
	hashwrapper *myWrapper = new md5wrapper();
	
	myWrapper->resetContext();
	myWrapper->updateContext(data.get_data(), data.get_lenght());
	

std::string hash1 = myWrapper->hashIt();
delete myWrapper;

return hash1;
}


