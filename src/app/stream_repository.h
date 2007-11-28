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
#include "../codecs/mdc/md_stream.h"
#include <map>
#include <string>


#ifndef STREAM_REPOSITORY_H_
#define STREAM_REPOSITORY_H_

class StreamRepository 
{
	
private:

	std::map<std::string, MDStream*> m_streams;
	
	bool m_is_valid;

public:
	
	void init(std::string path);

	std::vector<MDStream*> find_by_name(std::string regexp);
	
	bool get_by_hash(std::string hash, MDStream* &stream);
	
	void refresh();
	
	bool add_stream(MDStream* stream);
	
	void deinit();

	// begin Singleton stuff

private:

static StreamRepository* _instance;

protected:

StreamRepository():m_is_valid(false){};
~StreamRepository(){deinit();}

public:

static StreamRepository* instance();

// end Singleton stuff

};

#endif /*STREAM_REPOSITORY_H_*/
