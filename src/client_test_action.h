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

#include "defs.h"
#include "common/action.h"

#ifndef CLIENT_TEST_ACTION_H_
#define CLIENT_TEST_ACTION_H_

/**
 * Client Test Class.
 * Its action sends a UDP packet to the server every 5 seconds
*/
class ClientTestAction: public Action
{
private:
	
	
public:
	
	ClientTestAction(){};
	
	void action();
};


#endif /*CLIENT_TEST_ACTION_H_*/
