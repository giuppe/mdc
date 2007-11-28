
#ifndef CLIENT_MANAGER_H_
#define CLIENT_MANAGER_H_

#include "defs.h"
#include "../mdc_messages.h"
#include "../common/net_end_point.h"

class ClientManager
{
public:
	ClientManager(){}
	void handle_ALST(const NetEndPoint& sender, const MDCMessageAlst& msg);
	void handle_APER(const NetEndPoint& sender, const MDCMessageAper& msg);
	void handle_ASNF(const NetEndPoint& sender, const MDCMessageAsnf& msg);
		
};

#endif /*CLIENT_MANAGER_H_*/
