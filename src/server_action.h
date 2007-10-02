/***************************************************************************
                          server_action.h  -  Insert description
                             -------------------
    begin                : Jul 25, 2007
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
#include "common/action.h"

#ifndef SERVER_ACTION_H_
#define SERVER_ACTION_H_

class StreamRepository;

class ServerAction : public Action
{
private:
	StreamRepository* m_stream_repository;
	
	Uint32 m_listening_socket;
public:
	
	ServerAction();
	
	void action();
	
	
};


#endif /*SERVER_ACTION_H_*/
