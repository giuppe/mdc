/***************************************************************************
                          stream_repository.h  -  Insert description
                             -------------------
    begin                : Sep 14, 2007
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

#include "defs.h"
#include "md_stream.h"
#include <vector>
#include <string>


#ifndef STREAM_REPOSITORY_H_
#define STREAM_REPOSITORY_H_

class StreamRepository 
{
	
private:

	std::vector<MDStream*> m_streams;
	
	bool m_is_valid;

public:
	
	StreamRepository(std::string path);

	~StreamRepository();
	
	std::vector<MDStream*> find_by_name(std::string regexp);


};

#endif /*STREAM_REPOSITORY_H_*/
