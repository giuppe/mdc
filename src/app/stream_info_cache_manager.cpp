
#include "defs.h"
#include "stream_info_cache_manager.h"




string StreamInfoCacheManager::get_name(string stream_id)
{
	map<string, NameInfoEntry>::const_iterator it;
			
	it = m_stream_names.find(stream_id);
			
	if(it==m_stream_names.end())
	{
		LOG_ERROR("Info for stream_id "<<stream_id<<" not cached.");
		return "";
	}
	
	return it->second.name;
		
}

void StreamInfoCacheManager::add_name(string stream_id, string name)
{
	m_stream_names[stream_id].name= name;
}

MDStreamInfo StreamInfoCacheManager::get_info(string stream_id)
{
	map<string, NameInfoEntry>::const_iterator it;
				
	it = m_stream_names.find(stream_id);
				
	if(it==m_stream_names.end())
	{
		LOG_ERROR("Info for stream_id "<<stream_id<<" not cached.");
		MDStreamInfo temp;
		return temp;
	}
	
	return it->second.info;
		
}

void StreamInfoCacheManager::add_info(string stream_id, MDStreamInfo info)
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
