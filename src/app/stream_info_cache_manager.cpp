
#include "defs.h"
#include "stream_info_cache_manager.h"
#include <string>
#include <map>


std::string StreamInfoCacheManager::get_name(std::string stream_id)
{

	return m_stream_names.at(stream_id).name;
		
}

void StreamInfoCacheManager::add_name(std::string stream_id, std::string name)
{
	m_stream_names[stream_id].name= name;
}

MDStreamInfo StreamInfoCacheManager::get_info(std::string stream_id)
{
	return m_stream_names.at(stream_id).info;
		
}

void StreamInfoCacheManager::add_info(std::string stream_id, MDStreamInfo info)
{
	m_stream_names[stream_id].info= info;
}

StreamInfoCacheManager* StreamInfoCacheManager::_instance = 0;

StreamInfoCacheManager* StreamInfoCacheManager::instance()
{
	if(_instance==0)
	{
		_instance=new StreamInfoCacheManager();
	}
	return _instance;
}
