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



#ifndef STREAM_REPOSITORY_H_
#define STREAM_REPOSITORY_H_

#include "defs.h"
#include "../codecs/mdc/md_stream.h"



struct RepositoryEntry
{
	string name;
	MDStream* stream;
};


class StreamRepository 
{
	
private:

	map<string, RepositoryEntry> m_streams;
	
	bool m_is_valid;
	
	string m_path;

public:
	
	void init(string path);

	vector<MDStream*> find_by_name(string regexp);
	
	bool get_by_stream_id(string stream_id, MDStream* &stream);
	
	void refresh();
	
	bool add_stream(RepositoryEntry entry);
	
	string get_name_by_id(string stream_id);
	
	void create_stream(string name, string stream_id, Uint8 flows, Uint32 sequences);
	
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
