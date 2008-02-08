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
#include "app/client_manager.h"

enum{ASK_LIST, ASK_INFO, ASK_FILE, STOP_AND_WAIT, EXIT};

void ClientTestAction::init(string server1)
{
	m_state= ASK_LIST;
	m_exited = false;
	m_my_server1=NetEndPoint(server1, 5551);		
}

void ClientTestAction::action()
{
	switch(m_state)
	{
	case ASK_LIST:
		ask_list();
		sleep(5000);
		break;
	case ASK_INFO:
		ask_info();
		sleep(5000);
		break;

	case ASK_FILE:
		ask_file();
		break;
	case STOP_AND_WAIT:
		sleep(40000);
		m_state=EXIT;
		break;
	case EXIT:
		this->m_exited = true;
	default:
		break;
	}
	

}

void ClientTestAction::ask_list()
{
	string name("cap");


	ClientManager* cl_man = ClientManager::instance();
	cl_man->search(m_my_server1, name);

	m_state = ASK_INFO;

}

void ClientTestAction::ask_info()
{
	ClientManager* cl_man = ClientManager::instance();
	vector<SearchEntry> results = cl_man->get_last_search();
	if(results.size()>0)
	{
		for(Uint32 i=0; i<results.size(); i++)
		{
			LOG_INFO("Found stream "<<results[i].get_name());
		}
		LOG_INFO("Selecting stream with stream_id="<<results[0].get_stream_id());

		m_selected_file_stream_id = results[0].get_stream_id();

		cl_man->request_stream_info(m_my_server1, m_selected_file_stream_id);
		m_state = ASK_FILE;
	}
	else
	{
		LOG_INFO("No results found.");
		m_state = ASK_LIST;
	}

}

void ClientTestAction::ask_file()
{
	ClientManager* cl_man = ClientManager::instance();
	MDStreamInfo info = cl_man->get_last_stream_info();
	if(info.stream_id==m_selected_file_stream_id)
	{

		LOG_INFO("Stream "<<info.stream_id<<" has "<<info.flows_number<<" flows and "<<info.descriptors_number<<" descriptors");

		for(Uint32 i=0; i<info.flows_number; i++)
		{


			//LOG_INFO("Downloading flow "<<i);

			cl_man->request_stream(m_my_server1, m_selected_file_stream_id, i, 0, info.descriptors_number-1);
		//	cl_man->request_stream(m_my_server2, m_selected_file_stream_id, 0, 0, info.descriptors_number-1);
		}
		m_state = STOP_AND_WAIT;
	}
	else
	{
		LOG_INFO("No stream with id "<<m_selected_file_stream_id<<"found.");
		m_state = ASK_LIST;
	}

}
