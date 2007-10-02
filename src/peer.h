/***************************************************************************
                          peer.h  -  Insert description
                             -------------------
    begin                : Aug 20, 2007
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

#ifndef PEER_H_
#define PEER_H_

/**
 * Class Peer contains informations about a peer in the network.
 */
class Peer
{
private:
	char* m_hostname;
	Uint16 m_port;
	
};

#endif /*PEER_H_*/
