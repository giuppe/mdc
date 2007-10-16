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
	std::vector<std::string> get_file_names(std::string path);
	
	bool load_file(const std::string& path, DataChunk& loaded_data);
};

#endif /*POSIX_DIRECTORY_H_*/
