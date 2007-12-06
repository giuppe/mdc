
#ifndef STREAM_NAME_CACHE_MANAGER_H_
#define STREAM_NAME_CACHE_MANAGER_H_

#include "defs.h"
#include <string>
#include <map>
#include "../codecs/mdc/md_stream.h"

class StreamInfoCacheManager
{
private:

	struct NameInfoEntry
	{
		std::string name; 
		MDStreamInfo info; 
		NameInfoEntry(){}
	};
	std::map<std::string, NameInfoEntry> m_stream_names;
	
public:
	
	std::string get_name(std::string stream_id);
	
	void add_name(std::string stream_id, std::string name);

	MDStreamInfo get_info(std::string stream_id);
	
	void add_info(std::string stream_id, MDStreamInfo info);

	
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
