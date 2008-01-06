/***************************************************************************
                          directory_factory.h  -  Insert description
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


#ifndef DIRECTORY_FACTORY_H_
#define DIRECTORY_FACTORY_H_

class DirectoryFactory
{
private:
	static AbstractDirectory* m_directory;
public:

	

	static AbstractDirectory* createDirectory();
};

#endif /*DIRECTORY_FACTORY_H_*/
