/***************************************************************************
                          posix_directory.h  -  Insert description
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

#include "abstract_directory.h"
#include <vector>
#include <string>



#ifndef POSIX_DIRECTORY_H_
#define POSIX_DIRECTORY_H_


class PosixDirectory : public AbstractDirectory
{
public:
	vector<string> get_file_names(string path);
	
	bool load_file(const string& path, DataChunk& loaded_data);

	bool save_file(const string& path, const DataChunk& data_to_save);
	
	string get_filename(const string& path);
	
	//string get_hash_md5(const string& path);

	
};

#endif /*POSIX_DIRECTORY_H_*/
