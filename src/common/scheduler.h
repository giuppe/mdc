/***************************************************************************
                          scheduler.h  -  Generic actions scheduler
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
#include "action.h"
#include <list>

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

/**
 * Defines a scheduler for Action s' execution.
 */
class Scheduler
{
protected:

	list<Action*> m_actions;
	
private:
	Uint32 m_last_tick;
	
public:
	
	/**
	 * Scheduler constructor.
	 */
	Scheduler();
	
	/**
	 * Add an Action to the schedule list.
	 * @param action the action to add to execution list.
	 */
	void add_action(Action* action);
	
	/**
	 * Executes all non-suspended Action s in the schedule.
	 * It cycles through all Action s scheduled, executing their action() only one time.
	 */
	void execute_all();

};

#endif /*SCHEDULER_H_*/
