


#ifndef SITE_MANAGER_H_
#define SITE_MANAGER_H_

#include "defs.h"
#include "../common/action.h"
#include "control_manager.h"
#include "receive_manager.h"
#include "client_manager.h"

class SiteManager : public Action
{
private:
	Uint32 m_listening_socket;
	
	ControlManager m_sending_manager;
	
	ReceiveManager m_receive_manager;

	void pre_action(){}
	
	void post_action(){}
	
public:
	SiteManager();
	
	
	void action();
	
	~SiteManager();
	
};

#endif /*SITE_MANAGER_H_*/
