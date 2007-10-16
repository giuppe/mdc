/***************************************************************************
                          posix_directory.cpp  -  Insert description
                             -------------------
    begin                : 04/ott/07
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


#include "posix_directory.h"
#include "../log/log_manager.h"
#include "../data_chunk.h"
#include <sys/types.h>
#include <dirent.h>
#include <cerrno>


std::vector<std::string> PosixDirectory::get_file_names(std::string path)
{
	std::vector<std::string> result;
	
	DIR* directory;
		
		struct dirent* directory_entry;
		
		if( (directory = opendir(path.c_str())) == NULL ) 
		{
		        LOG_ERROR("Error opening "<<path.c_str());
		        switch(errno)
		        {
		        case ENOENT:
		        	LOG_ERROR("Path not exists.");
		        	break;
		        default:
		        	LOG_ERROR("Filesystem error: "<<errno);
		        	
		        }
		        return result;
		}
		
		while((directory_entry = readdir(directory)))
		{
			if ((strcmp(directory_entry->d_name, ".") == 0 ||  strcmp(directory_entry->d_name, "..") == 0))
			{
			      continue;
			}
			LOG_INFO("File found: "<<directory_entry->d_name);
			result.push_back(directory_entry->d_name);
		}
		
		return result;
}



bool PosixDirectory::load_file(const std::string& path, DataChunk& loaded_data)
{
	loaded_data.erase();
	FILE *m_f;
	Uint8 c;
	if (path.size() > 0)
	{
		if (fopen(path.c_str(), "r") != NULL)
		{
			m_f = fopen(path.c_str(), "r");
			while (fscanf(m_f, "%c", &c) > 0) 
			{
				loaded_data.append(c);
			}
			fclose(m_f);
			return true;
		}
		else return false;
	}
	return false;
}
