/***************************************************************************
                          client_test_action.h  -  Insert description
                             -------------------
    begin                : 
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



#ifndef CLIENT_TEST_ACTION_H_
#define CLIENT_TEST_ACTION_H_

#include "defs.h"
#include "common/action.h"
#include "common/net_manager.h"

/**
 * Client Test Class.
 * Its action sends a UDP packet to the server every 5 seconds
*/
class ClientTestAction: public Action
{
private:
	Uint32 m_state;
	
	std::string m_selected_file_stream_id;
	
	NetEndPoint m_my_server;
	void pre_action(){}
		
		void post_action(){}
public:
	
	ClientTestAction(){init();};
	
	void init();
	
	void action();
	
private:
	void ask_list();
	void ask_info();
	void ask_file();
};


#endif /*CLIENT_TEST_ACTION_H_*/
