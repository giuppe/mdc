
#ifndef ACTION_TIMED_H_
#define ACTION_TIMED_H_

#include "defs.h"
#include "action.h"

class ActionTimed : public Action
{
protected:
	Uint32 m_maximum_time;
	
	Uint32 m_start_time;

public:
	ActionTimed(){init();}
	
	void init(){m_maximum_time=100;Action::init();}
	
	Uint32 get_maximum_time(){return m_maximum_time;}
	
	void set_maximum_time(Uint32 maximum_time){m_maximum_time=maximum_time;}
	
	void pre_action(){m_start_time = SDL_GetTicks();}
	
	bool is_elapsed_maximum_time(){if(m_start_time+m_maximum_time>SDL_GetTicks()){LOG_INFO("Time elapsed, sleeping action"); return true;}return false;}
	
	void post_action(){m_start_time = 0;}
};

#endif /*ACTION_TIMED_H_*/
