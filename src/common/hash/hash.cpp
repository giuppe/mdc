
#include "defs.h"
#include "hash.h"
#include "hashlibpp/hl_hashwrapper.h"
#include "hashlibpp/hl_md5wrapper.h"


string Hash::md5_from_file(string path)
{
	/*
	 * creating a wrapper object
	 */
	hashwrapper *myWrapper = new md5wrapper();



	/*
	 * create a hash based on a file
	 */
	string hash2 = myWrapper->getHashFromFile(path);

	delete myWrapper;

	return hash2;
}

string Hash::md5_from_string(string str)
{
	/*
	 * creating a wrapper object
	 */
	hashwrapper *myWrapper = new md5wrapper();



	/*
	 * create a hash from a string
	 */
	string hash1 = myWrapper->getHashFromString(str);
	delete myWrapper;

	return hash1;
}

string Hash::md5_from_datachunk(const DataChunk& data)
{

	hashwrapper *myWrapper = new md5wrapper();

	myWrapper->resetContext();
	myWrapper->updateContext(data.get_data(), data.get_lenght());


	string hash1 = myWrapper->hashIt();
	delete myWrapper;

	return hash1;
}


