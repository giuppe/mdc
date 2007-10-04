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

/**
 * Loads all MDC streams found in path.
 * @param path path of mdc files
 */
StreamRepository::StreamRepository(std::string path)
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
				m_streams.push_back(curr_stream);
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
	
	for(Uint32 i=0; i<m_streams.size(); i++)
	{
		curr_stream_name = m_streams[i]->get_name();
		std::string::size_type found = curr_stream_name.find(regexp);
		if(found != std::string::npos)
		{
			results.push_back(m_streams[i]);
		}
	}
	
	return results;
	
}



StreamRepository::~StreamRepository()
{
	for(Uint32 i = 0; i<m_streams.size(); i++)
	{
		delete m_streams[i];
	}
}

