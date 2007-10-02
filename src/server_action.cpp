/***************************************************************************
                          server_action.cpp  -  Insert description
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
#include "server_action.h"
#include "common/data_chunk.h"
#include "common/net_manager.h"
#include "mdc_messages.h"
#include "codecs/md_stream.h"
#include "codecs/stream_repository.h"

ServerAction::ServerAction()
{
	m_listening_socket = NetManager::instance()->create_UDP_listen_socket("localhost", 5555);
	LOG_INFO("Server listening on port 5555");
	m_stream_repository = new StreamRepository("~/repo_mdc");
}


void ServerAction::action()
{

	DataChunk received;
	
	Uint32 sender_address;
	
	Uint16 sender_port;
	
	if(NetManager::instance()->receive_data(m_listening_socket, received, sender_address, sender_port))
	{
	
		MDCMessage msg;
		msg.deserialize(received);
		LOG_INFO("Received packet, of type: "<<msg.get_type_string());
		
		if(strcmp(msg.get_type_string(), "LIST")==0)
		{
			MDCMessageList msg_list;
			msg_list.deserialize(received);
			LOG_INFO("Content is "<<msg_list.get_parameter());
			std::vector<MDStream*> stream_list;
									
			stream_list = m_stream_repository->find_by_name(msg_list.get_parameter());
			
			std::vector<std::string> rows;
			rows.resize(stream_list.size());
			
			for(Uint32 i=0; i<stream_list.size(); i++)
			{
				std::string msg_entry;
				msg_entry="h=";
				msg_entry+=stream_list[i]->get_hash();
				msg_entry+=";";
				msg_entry+="n=";
				msg_entry+=stream_list[i]->get_name();
				msg_entry+=";";
				rows[i] = msg_entry;
			}
			
			MDCMessageAlst response;
						
			response.set_rows(rows);
			
			Uint32 dest_socket = NetManager::instance()->create_UDP_socket(sender_address, sender_port);
			NetManager::instance()->send_data(dest_socket, response.serialize());
			
		}
		if(strcmp(msg.get_type_string(), "APER")==0)
		{
			MDCMessageAper msg_aper;
			msg_aper.deserialize(received);
			std::vector<std::string> peer_list = msg_aper.get_rows();
			for(Uint32 i = 0; i< peer_list.size(); i++)
			{
				LOG_INFO("Content is "<<peer_list[i]);
			}
		}


	}

}

