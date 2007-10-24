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
#include <cassert>
#include <string>

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



bool PosixDirectory::save_file(const std::string& path, const DataChunk& data_to_save)
{
	
	//FIXME: posix_directory can save files < 4MB only
	
	DataChunk dc;
	dc+=data_to_save;
	
	FILE *m_f;

	Uint8 byte;

	if (path.size() > 0)
	{
		if (fopen(path.c_str(), "w") != NULL) 
		{
			m_f = fopen(path.c_str(), "w");
			for (Uint32 i=0; i<dc.get_lenght(); i++)
			{
				//write characters
				dc.extract_head(byte);
				fputc(byte, m_f);
			}
			
			fclose(m_f);
			return true;
		}
	}
	
	return false;
	
}

std::string PosixDirectory::get_filename(const std::string& path)
{
	std::string::size_type pos = path.find_last_of('/');
	return path.substr(pos);
}


std::string PosixDirectory::get_hash_md5(const std::string& path)
{
	LOG_ERROR("This function is a stub - returns always md5 for <livio rulez>");
	return std::string("3b3f9dabbc0cf273e51f04f84b383b1d");
}



