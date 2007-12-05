/***************************************************************************
                          stream_repository.cpp  -  Insert description
                             -------------------
    begin                : Sep 14, 2007
    copyright          : (C) 2007 by Giuseppe D'Aqui'
    email                : giuseppe.da@gmail.com
 ***************************************************************************/

/***************************************************************************
 *                                                                                                                 
 *   This program is free software; you can redistribute it and/or modify  
 *   it under the terms of the GNU General Public License, Version 2,        
 *   as published by the Free Software Foundation.                                  
 *                                                                                                                 
 ***************************************************************************/

#include "defs.h"
#include "stream_repository.h"
#include "../common/dir/directory_factory.h"
#include <cassert>

/**
 * Loads all MDC streams found in path.
 * @param path path of mdc files
 */
void StreamRepository::init(std::string path)
{
	m_is_valid = false;
	
	AbstractDirectory* dir = DirectoryFactory::createDirectory();
	
	std::vector<std::string> files = dir->get_file_names(path);
	
	for(Uint32 i = 0; i<files.size(); i++)
	{
		std::string::size_type found = files[i].find(".mdc");
		if(found != std::string::npos)
		{
			MDStream* curr_stream = new MDStream();
			std::string complete_path = path+files[i];
			curr_stream->load_from_disk(complete_path);
			if(curr_stream->is_empty()==false)
			{
				m_streams.insert(make_pair(dir->get_hash_md5(complete_path), curr_stream));
			}
			else
			{
				delete curr_stream;
			}
		}
	}
	        
	m_is_valid = true;
}



std::vector<MDStream*> StreamRepository::find_by_name(std::string regexp)
{
	std::vector<MDStream*> results;
	
	std::string curr_stream_name;
	
	std::map<std::string,MDStream*>::iterator iter;
	for( iter = m_streams.begin(); iter != m_streams.end(); ++iter ) 
	{
		curr_stream_name = iter->second->get_name();
		std::string::size_type found = curr_stream_name.find(regexp);
		if(found != std::string::npos)
		{
			results.push_back(iter->second);
		}
	}
	
	return results;
	
}



void StreamRepository::deinit()
{
	std::map<std::string,MDStream*>::iterator iter;
	for( iter = m_streams.begin(); iter != m_streams.end(); ++iter ) 
	{
		delete iter->second;
	}
}



bool StreamRepository::get_by_hash(std::string hash, MDStream* &stream)
{
	if(m_streams.count(hash)==1)
	{
		stream=m_streams.at(hash);
		return true;
	}
	
	return false;
}

void StreamRepository::refresh()
{
	assert(!"This function is a stub.");
	
}


bool StreamRepository::add_stream(MDStream* stream)
{

	if(stream->is_empty())
	{
		LOG_ERROR("Adding an empty stream: so I do nothing");
		return false;
	}
	
	std::string hash = stream->get_stream_id();
	m_streams.insert(make_pair(hash, stream));
	
	return true;
	
}



StreamRepository* StreamRepository::_instance = 0;

StreamRepository* StreamRepository::instance()
{
	if(_instance==0)
	{
		_instance=new StreamRepository();
	}
	return _instance;
}

