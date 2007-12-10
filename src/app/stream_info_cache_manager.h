
#ifndef STREAM_NAME_CACHE_MANAGER_H_
#define STREAM_NAME_CACHE_MANAGER_H_

#include "defs.h"


#include "../codecs/mdc/md_stream.h"

class StreamInfoCacheManager
{
private:

	struct NameInfoEntry
	{
		string name; 
		MDStreamInfo info; 
		NameInfoEntry(){}
	};
	map<string, NameInfoEntry> m_stream_names;
	
public:
	
	string get_name(string stream_id);
	
	void add_name(string stream_id, string name);

	MDStreamInfo get_info(string stream_id);
	
	void add_info(string stream_id, MDStreamInfo info);

	
	// begin Singleton stuff

private:

static StreamInfoCacheManager* _instance;

protected:

StreamInfoCacheManager(){};
~StreamInfoCacheManager(){}

public:

static StreamInfoCacheManager* instance();

// end Singleton stuff

};



#endif /*STREAM_NAME_CACHE_MANAGER_H_*/
