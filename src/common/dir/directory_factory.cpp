/***************************************************************************
                          directory_factory.cpp  -  Insert description
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
#include "directory_factory.h"
#include "posix_directory.h"

AbstractDirectory* DirectoryFactory::m_directory = 0;

AbstractDirectory* DirectoryFactory::createDirectory()
{
	
	if(m_directory==0)
	{
		//FIXME: should support other directory types, now only posix
		m_directory = new PosixDirectory();
	}
	return m_directory;
}
