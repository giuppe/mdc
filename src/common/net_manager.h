/***************************************************************************
                          net_manager.h  -  Net Manager class
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
#include <string>
#include <vector>
#include "net_end_point.h"
#include "data_chunk.h"

#ifndef NET_MANAGER_H_
#define NET_MANAGER_H_
/**
 * Singleton used for managing network-related actions.
 * Permits to send and receive DataChunk s.
 */
class NetManager
{
private:
	std::vector<UDPsocket> m_sockets;
	
	std::vector<IPaddress> m_addresses;
	
	UDPsocket get_socket(Uint32 socket_handle);
	
public:
	void init();
	
	void deinit();
	
	/**
	 * Creates an UDP listening Socket (e.g. for data reception), and returns an handle to it.
	 * @param address the local address of the listening interface
	 * @param port the local listening port
	 * @returns handle to the listening socket.
	 */
	Uint32 create_UDP_listen_socket(const std::string& address, Uint16 port);
	
	/**
		 * Creates an UDP generic Socket (e.g. for data sending), and returns an handle to it.
		 * @param address the local address of the listening interface
		 * @param port the local listening port
		 * @returns handle to the listening socket.
		 */
	Uint32 create_UDP_socket(const std::string& address, Uint16 port);
	
	
	Uint32 create_UDP_socket(Uint32 address, Uint16 port);
	
	/**
		 * Sends a DataChunk through a previously created socket.
		 * @param destination the endpoint of the destination.
		 * @param data the DataChunk to send.
		 */
	void send_data(NetEndPoint destination, const DataChunk& data);
	
	/**
		 * Receive a DataChunk through a previously created listening socket.
		 * @param source_socket_handle an handle of the listening socket.
		 * @param data object filled with received data.
		 * @returns true if data received.
		 */
	bool receive_data(Uint32 source_socket_handle, DataChunk& data, Uint32& sender_address, Uint16& sender_port);
	
	
	Uint32 resolve(std::string hostname);
	
	
		// begin Singleton stuff

private:

    static NetManager* _instance;

protected:

	NetManager(){};
	~NetManager(){deinit();}

public:

    static NetManager* instance();

// end Singleton stuff
};

#endif /*NET_MANAGER_H_*/
