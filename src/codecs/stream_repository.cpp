/***************************************************************************
                          stream_repository.cpp  -  Insert description
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
#include "stream_repository.h"



std::vector<MDStream*> StreamRepository::find_by_name(std::string regexp)
{
	std::vector<MDStream*> results;
	
	std::string curr_stream_name;
	
	for(Uint32 i=0; i<m_streams.size(); i++)
	{
		curr_stream_name = m_streams[i]->get_name();
		std::string::size_type found = curr_stream_name.find(regexp);
		if(found != std::string::npos)
		{
			results.push_back(m_streams[i]);
		}
	}
	
	return results;
	
}