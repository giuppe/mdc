/***************************************************************************
                          abstract_directory.h  -  Insert description
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

#include <vector>

#ifndef ABSTRACT_DIRECTORY_H_
#define ABSTRACT_DIRECTORY_H_

class DataChunk;

class AbstractDirectory
{
public:
	virtual std::vector<std::string> get_file_names(std::string path) = 0;
	
	virtual bool load_file(const std::string& path, DataChunk& loaded_data) = 0;
	
	virtual bool save_file(const std::string& path, const DataChunk& data_to_save) = 0;
	
	virtual std::string get_filename(const std::string& path) = 0;
	
	virtual std::string get_hash_md5(const std::string& path) = 0;
		
	virtual ~AbstractDirectory(){}
};

#endif /*ABSTRACT_DIRECTORY_H_*/
