//============================================================================
// Name        : mdc.cpp
// Author      : Giuseppe D'Aqui'
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "common/net_manager.h"
#include "common/data_chunk.h"
#include <cstdlib>
#include "defs.h"
#include <SDL/SDL.h>
#include "common/scheduler.h"
#include "server_action.h"
#include "client_test_action.h"

using namespace std;

void deinit_all();

int main() {

	atexit(deinit_all);

	SDL_Init(SDL_INIT_TIMER);
	LogManager::instance()->init(true, "./mdc_log.txt");
	NetManager::instance()->init();
	DEBUG_OUT("!!!Hello World!!!\n");
	
	SDL_Delay(1000);
	
	Scheduler* sched = new Scheduler();
	ServerAction* server = new ServerAction();
	
	ClientTestAction* client = new ClientTestAction();
	
	
	sched->add_action(server);
	
	sched->add_action(client);
	
	server->start();
	
	client->start();
	
	Uint32 times = 100;
	while(--times != 0)
	{
		sched->execute_all();
		SDL_Delay(100);
	}
	
	delete server;
	delete client;
	delete sched;
	
	return 0;
}

void deinit_all()
{
	NetManager::instance()->deinit();
	
	LogManager::instance()->deinit();
}

