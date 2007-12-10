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


vector<string> PosixDirectory::get_file_names(string path) {
	vector<string> result;
	DIR* directory;
	struct dirent* directory_entry;
	if ((directory = opendir(path.c_str())) == NULL) {
		LOG_ERROR("Error opening "<<path.c_str());
		switch(errno) {
		case ENOENT:
			LOG_ERROR("Path not exists.");
			break;
		default:
			LOG_ERROR("Filesystem error: "<<errno);
		}
		return result;
	}
	while ((directory_entry = readdir(directory))) {
		if ((strcmp(directory_entry->d_name, ".")==0 || strcmp(directory_entry->d_name, "..")==0))
			continue;
		LOG_INFO("File found: "<<directory_entry->d_name);
		result.push_back(directory_entry->d_name);
	}
	return result;
}

bool PosixDirectory::load_file(const string& path, DataChunk& loaded_data) {
	loaded_data.erase();
	FILE *m_f;

	Uint64 lSize;
	Uint8* buffer;
	size_t result;
	
	if (path.size() > 0)
	{
		m_f = fopen(path.c_str(), "r");
			
		if (m_f != NULL) 
		{
			// obtain file size:
			fseek (m_f , 0 , SEEK_END);
			lSize = ftell (m_f);
			rewind (m_f);

			// allocate memory to contain the whole file:
			buffer = new Uint8[lSize];
			
			result = fread (buffer,1,lSize,m_f);
			
			if (result != lSize)
			{
				LOG_ERROR("Reading error on file "<<path);
				return false;
			}

			loaded_data.append(lSize, buffer);
			delete[] buffer;
			fclose(m_f);
			return true;
		}
	}
	
	return false;
}

bool PosixDirectory::save_file(const string& path, const DataChunk& data_to_save) {
	//FIXME: always overwrite to output file
	DataChunk dc;
	dc += data_to_save;
	FILE *m_f;
	Uint64 lSize;
	Uint8* buffer;
	size_t result;
	
	if (path.size() > 0)
	{
		m_f = fopen(path.c_str(), "w");
		if (m_f != NULL) 
		{
			lSize = dc.get_lenght();
			
			dc.extract_head(lSize, buffer);
			
			result = fwrite (buffer,1,lSize,m_f);
						
			if (result != lSize)
			{
				LOG_ERROR("Write error on file "<<path);
				return false;
			}
			
			fclose(m_f);
			return true;
		}
	}
	return false;
}

string PosixDirectory::get_filename(const string& path) {

	string::size_type pos = 0;
	string::size_type last_pos = 0;
	while(pos!=string::npos)
	{
		pos=path.find('/');
		last_pos = pos;
	}
#ifdef USING_USTL
	return UstlUtils::string_substr(path, last_pos+1);
#else
	return path.substr(last_pos+1);
#endif
}
