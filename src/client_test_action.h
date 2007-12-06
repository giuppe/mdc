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
	
	bool m_exited;
	
	std::string m_selected_file_stream_id;
	
	NetEndPoint m_my_server1;
	
	NetEndPoint m_my_server2;
	
	void pre_action(){}
		
		void post_action(){}
		
	void exit_action(){m_exited=true;}
public:
	
	ClientTestAction(){};
	
	void init(std::string server1, std::string server2);
	
	void action();
	
	bool is_action_exited(){return m_exited;}
	
private:
	void ask_list();
	void ask_info();
	void ask_file();
};


#endif /*CLIENT_TEST_ACTION_H_*/
