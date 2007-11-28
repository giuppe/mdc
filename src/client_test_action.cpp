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
#include "common/udp_message.h"
#include "mdc_messages.h"

void ClientTestAction::action()
{
	MDCMessageAper msg;
	std::vector<std::string> peer_list;
	peer_list.push_back("192.168.0.1:4567");
	peer_list.push_back("192.168.0.4:4567");
		
	msg.set_rows(peer_list);
	
	UDPMessage udp_msg;
	udp_msg.set_destination(NetEndPoint(NetManager::instance()->resolve("127.0.0.1"), 5551));
	udp_msg.set_payload(msg.serialize());

	udp_msg.send();
	
	sleep(5000);
}
