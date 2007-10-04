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

class AbstractDirectory
{
public:
	virtual std::vector<std::string> get_file_names(std::string path) = 0;
};

#endif /*ABSTRACT_DIRECTORY_H_*/
