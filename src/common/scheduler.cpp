/***************************************************************************
                          scheduler.cpp  -  Generic Actions scheduler
                             -------------------
    begin                : Jul 13, 2007
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
#include <list>
#include "scheduler.h"





Scheduler::Scheduler()
{
	m_last_tick = SDL_GetTicks();
}



void Scheduler::add_action(Action* action)
{
	m_actions.push_back(action);
	LOG_INFO("Added action of type "<<typeid(action).name());
}

void Scheduler::execute_all()
{
	list<Action*>::iterator it;
	
	Uint32 tick_diff;
	Uint32 action_to_sleep;
	for ( it=m_actions.begin() ; it != m_actions.end(); it++ )
	{
		
		tick_diff = SDL_GetTicks()-m_last_tick;
		
		if(!((*it)->is_suspended()))
		{
			
			action_to_sleep = (*it)->get_sleep_time();
		
			if(action_to_sleep==0)
			{
				(*it)->pre_action();
				(*it)->action();
				(*it)->post_action();
			}
			else
			{
				if(action_to_sleep<tick_diff)
					(*it)->sleep(0);
				else
					(*it)->sleep(action_to_sleep-tick_diff);
			}
			
			
		}
		
	}
	m_last_tick = SDL_GetTicks();
}
