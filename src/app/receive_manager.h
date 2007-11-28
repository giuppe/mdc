
#ifndef RECEIVE_MANAGER_H_
#define RECEIVE_MANAGER_H_

#include "defs.h"
#include "../mdc_messages.h"
#include "../common/net_end_point.h"

class ReceiveManager
{
public:
	ReceiveManager(){}
	void handle_ASRQ(const NetEndPoint& sender, const MDCMessageAsrq& msg);
	
};

#endif /*RECEIVE_MANAGER_H_*/
