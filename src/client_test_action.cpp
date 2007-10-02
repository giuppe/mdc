/***************************************************************************
                          client_test_action.cpp  -  Insert description
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

#include "defs.h"
#include "client_test_action.h"
#include "common/data_chunk.h"
#include "common/net_manager.h"
#include "mdc_messages.h"

void ClientTestAction::action()
{
	MDCMessageAper msg;
	std::vector<std::string> peer_list;
	peer_list.push_back("192.168.0.1:4567");
	peer_list.push_back("192.168.0.4:4567");
		
	msg.set_rows(peer_list);
	Uint32 dest_socket = NetManager::instance()->create_UDP_socket("localhost", 5555);
	NetManager::instance()->send_data(dest_socket, msg.serialize());
	sleep(5000);
}
