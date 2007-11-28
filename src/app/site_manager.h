


#ifndef SITE_MANAGER_H_
#define SITE_MANAGER_H_

#include "defs.h"
#include "../common/action.h"
#include "sending_manager.h"
#include "receive_manager.h"
#include "client_manager.h"

class SiteManager : public Action
{
private:
	Uint32 m_listening_socket;
	
	SendingManager m_sending_manager;
	
	ReceiveManager m_receive_manager;
	
	ClientManager m_client_manager;
	
public:
	SiteManager();
	
	
	void action();
};

#endif /*SITE_MANAGER_H_*/
