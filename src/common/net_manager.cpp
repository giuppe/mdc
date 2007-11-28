/***************************************************************************
                          net_manager.cpp  -  Net Manager class
                             -------------------
    begin                : Jul 13 2007
    copyright            : (C) 2007 by Giuseppe D'Aqui'
    email                : kumber@tiscalinet.it
 ***************************************************************************/

/***************************************************************************
 *                                                                                                                 
 *   This program is free software; you can redistribute it and/or modify  
 *   it under the terms of the GNU General Public License, Version 2,        
 *   as published by the Free Software Foundation.                                  
 *                                                                                                                 
 ***************************************************************************/


#include "defs.h"
#include <SDL/SDL_net.h>
#include "data_chunk.h"
#include <cassert>
#include <cstring>
#include "net_manager.h"


Uint32 NetManager::create_UDP_listen_socket(const std::string& address, Uint16 port)
{
	IPaddress ip_address;
	/*
	LOG_INFO("Resolving "<<address);
	
	Sint32 result = SDLNet_ResolveHost(&ip_address, address.c_str(), port);
	if(result !=0)
	{
		LOG_ERROR("Cannot resolve: "<<address);
	}
	*/
	ip_address.host = resolve(address);
	ip_address.port = port;
	LOG_INFO("Creating UDP socket on port "<<port);
	UDPsocket socket = SDLNet_UDP_Open(port);
	
	SDLNet_UDP_Bind(socket, -1, &ip_address);
	
	Uint32 socket_id = m_sockets.size();
	
	m_sockets.push_back(socket);
	
	m_addresses.push_back(ip_address);
		
	return socket_id;
}

Uint32 NetManager::create_UDP_socket(const std::string& address, Uint16 port)
{
	IPaddress ip_address;
	
	LOG_INFO("Resolving "<<address);
	
	Sint32 result = SDLNet_ResolveHost(&ip_address, address.c_str(), port);
	if(result !=0)
	{
		LOG_ERROR("Cannot resolve: "<<address);
	}
	
	return create_UDP_socket(ip_address.host, ip_address.port);
	
}



Uint32 NetManager::create_UDP_socket(Uint32 address, Uint16 port)
{
	IPaddress ip_address;
	ip_address.host = address;
	ip_address.port = port;
	
	LOG_INFO("Creating UDP socket on port "<<port);
		UDPsocket socket = SDLNet_UDP_Open(port);
		
		Uint32 socket_id = m_sockets.size();
		
		m_sockets.push_back(socket);
		
		m_addresses.push_back(ip_address);
			
		return socket_id;
	
	
}



void NetManager::init()
{
	LOG_INFO("Initializing NetManager.");
	if(SDLNet_Init()==-1) {
	    LOG_FATAL("Netmanager::init(): "<< SDLNet_GetError());
	    assert(0);
	}

}



void NetManager::deinit()
{
	LOG_INFO("De-initializing NetManager.");
	SDLNet_Quit();
}




UDPsocket NetManager::get_socket(Uint32 socket_handle)
{
	if(socket_handle < m_sockets.size())
	{
		return m_sockets[socket_handle];
	}
	LOG_FATAL("Accessing uninitialized socket.")
	exit(1);
	return 0;
}


void NetManager::send_data(Uint32 destination_socket_handle,  const DataChunk& data)
{
	//UDPsocket socket = get_socket(source_socket_handle);
	
	LOG_INFO("Allocating "<<data.get_lenght()<<" bytes for UDP packet");
	
	UDPpacket* packet = SDLNet_AllocPacket(data.get_lenght());
	
	if(!packet) 
	{
	    LOG_ERROR("NetManager::send_data(): "<<SDLNet_GetError());
	    assert(0);
	}
	else 
	{
	   //strncpy(packet->data,  data.get_data(), data.get_lenght());
	   
		memcpy(packet->data, data.get_data(), data.get_lenght());
		
		packet->len = data.get_lenght();
		
		LOG_INFO("Opening generic UDP socket");

		UDPsocket sd = SDLNet_UDP_Open(0);
	   
		packet->address = m_addresses[destination_socket_handle];
		
		LOG_INFO("Sending packet to "<< packet->address.host<<":"<<packet->address.port);
		
		if(SDLNet_UDP_Send(sd, -1, packet)==0)
		{
			LOG_ERROR("NetManager::send_data(): "<<SDLNet_GetError());
		}
		else
		{
			LOG_INFO("Packet sent.");
		}
		
		
	    // SDLNet_FreePacket this packet when finished with it
		SDLNet_FreePacket(packet);
		
	}
}




bool NetManager::receive_data(Uint32 source_socket_handle, DataChunk& data, Uint32 sender_address, Uint16 sender_port)
{
	UDPpacket packet;
	
	//FIXME: we assume that MTU is 1500
	packet.data = new Uint8[1500];
	
	UDPsocket udpsock = get_socket(source_socket_handle);
	
	Sint32 result = SDLNet_UDP_Recv(udpsock, &packet);
	
	switch(result)
	{
		case -1:
			delete [] packet.data;
			LOG_ERROR(SDLNet_GetError());
			break;
		case 0:
			return false;
			break;
		case 1:
			LOG_INFO("Received packet from "<<packet.address.host);
			data.set_content(packet.data, packet.len);
			sender_address = packet.address.host;
			sender_port = packet.address.port;
			return true;
		default:
			LOG_FATAL("SDLNet error: "<<SDLNet_GetError());
			assert(0);
	}
	return false;
	
}


Uint32 NetManager::resolve(std::string hostname)
{
	IPaddress ip_address;
		
		LOG_INFO("Resolving "<<hostname);
		
		Sint32 result = SDLNet_ResolveHost(&ip_address, hostname.c_str(), 0);
		
		if(result!=0)
		{
			LOG_ERROR("Cannot resolve: "<<hostname);
		}
		
		return ip_address.host;
		
}


NetManager* NetManager::_instance = 0;

NetManager* NetManager::instance()
{
	if(_instance==0)
	{
		_instance=new NetManager();
	}
	return _instance;
}


