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




#ifndef ABSTRACT_DIRECTORY_H_
#define ABSTRACT_DIRECTORY_H_

#include "../hash/hash.h"
#include "../defs.h"
#include "../data/file_data_chunk.h"


class AbstractDirectory
{
public:
	virtual vector<string> get_file_names(string path) = 0;
	
	virtual bool load_file(const string& path, FileDataChunk& loaded_data) = 0;
	
	virtual bool save_file(const string& path, const IDataChunk* data_to_save) = 0;
	
	virtual string get_filename(const string& path) = 0;
	
	string get_hash_md5(const string& path){return Hash::md5_from_file(path);}
		
	virtual ~AbstractDirectory(){}
};

#endif /*ABSTRACT_DIRECTORY_H_*/
