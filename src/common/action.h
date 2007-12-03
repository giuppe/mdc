/***************************************************************************
                          action.h  -  Generic abstract action
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

#ifndef ACTION_H_
#define ACTION_H_

class Scheduler;

/**
 * Represents an abstract Action to schedule for execution.
 * Inheriting classes must override the virtual function action().
 * An Action can be scheduled for execution through inertion into a Scheduler's 
 * execution list. 
 */
class Action
{
	friend class Scheduler;
protected:

	bool m_suspended;
	
	Uint32 m_sleep_time;
	
	void pre_action(){}
	
	void post_action(){}

public:
	
	/**
	 * Generic Action constructor. Sets the Action as suspended.
	 */
	Action(){init();}
	
	void init(){m_suspended=true;m_sleep_time=0;};
	
	/**
	 * Represents the actual instructions to execute. It must be overridden by inheriting classes.
	 */
	virtual void action() = 0;
	

	
	virtual ~Action(){};
	
	/**
	 * Tells if the action is suspended (e.g. if it won't be executed).
	 * @returns true if the action is suspended
	 */
	bool is_suspended(){return m_suspended;}

	/**
	 * Starts the Action, setting its suspended state as false.
	 */
	void start(){m_suspended = false;}

	/**
	 * Stops the Action, setting its suspended state as true.
	 */
	void stop(){m_suspended = true;}
	
	/**
	 * Stops the Action execution for at least msecs milliseconds.
	 * @param msecs the milliseconds to stop.
	 */
	void sleep(Uint32 msecs){m_sleep_time=msecs;};
	
	/**
	 * Tells the remaining sleep time.
	 * @returns the remaining sleep time in milliseconds.
	 */
	Uint32 get_sleep_time(){return m_sleep_time;};
	
};

#endif /*ACTION_H_*/
