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
void StreamRepository::init(string path)
{
	m_is_valid = false;
	
	m_path = path;
	
	AbstractDirectory* dir = DirectoryFactory::createDirectory();
	LOG_INFO("Initializing repository in "<<path);
	vector<string> files = dir->get_file_names(path);
	
	for(Uint32 i = 0; i<files.size(); i++)
	{
		LOG_INFO("Found file "<<files[i]);
		string::size_type found = files[i].find(".mdc");
		
		if(found != string::npos)
		{
			MDStream* curr_stream = new MDStream();
			string complete_path = path;
			complete_path+="/";
			complete_path+=files[i];
			curr_stream->load_from_disk(complete_path);
			if(curr_stream->is_empty()==false)
			{
				LOG_INFO("Adding "<<complete_path<<" to repository");
				RepositoryEntry entry;
				entry.name=files[i];
				entry.stream = curr_stream;
				add_stream(entry);
			}
			else
			{
				LOG_ERROR("Cannot load "<<complete_path);
				delete curr_stream;
			}
		}
	}
	        
	m_is_valid = true;
}



vector<MDStream*> StreamRepository::find_by_name(string regexp)
{
	vector<MDStream*> results;
	
	string curr_stream_name;
	LOG_INFO("Searching in repository for "<<regexp);
	map<string,RepositoryEntry>::iterator iter;
	for( iter = m_streams.begin(); iter != m_streams.end(); ++iter ) 
	{
		
		curr_stream_name = iter->second.name;
		LOG_INFO("Comparing "<<curr_stream_name);
		string::size_type found = curr_stream_name.find(regexp);
		if(found != string::npos)
		{
			LOG_INFO("Found "<<curr_stream_name);
			results.push_back(iter->second.stream);
		}
	}
	
	return results;
	
}



void StreamRepository::deinit()
{
	map<string,RepositoryEntry>::iterator iter;
	for( iter = m_streams.begin(); iter != m_streams.end(); ++iter ) 
	{
		string complete_path = m_path;
		complete_path+="/";
		complete_path+=iter->second.name;
		iter->second.stream->save_to_disk(complete_path);
		delete iter->second.stream;
	}
}



bool StreamRepository::get_by_stream_id(string stream_id, MDStream* &stream)
{
	map<string, RepositoryEntry>::const_iterator it;
				
		it = m_streams.find(stream_id);
				
		if(it==m_streams.end())
		{
			LOG_ERROR("Stream with stream_id "<<stream_id<<" not in repository.");
			return false;
		}
		
		stream = it->second.stream;
		return true;
	

}

void StreamRepository::refresh()
{
	assert(!"This function is a stub.");
	
}


bool StreamRepository::add_stream(RepositoryEntry entry)
{
	
	if(entry.stream->is_empty())
	{
		LOG_ERROR("Adding an empty stream: so I do nothing");
		return false;
	}
	
	string hash = entry.stream->get_stream_id();
	m_streams.insert(make_pair(hash, entry));
	LOG_INFO("Adding stream with id "<<hash<<", name "<<entry.name);
	
	return true;
	
}


string StreamRepository::get_name_by_id(string stream_id)
{
	return m_streams[stream_id].name;
}


void StreamRepository::create_stream(string name, string stream_id, Uint8 flows, Uint32 sequences)
{
	MDStream* new_stream = new MDStream(stream_id, flows, sequences);
	RepositoryEntry new_entry;
	new_entry.name=name;
	new_entry.stream = new_stream;
	m_streams.insert(make_pair(stream_id, new_entry));
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

