


#ifndef SENDING_MANAGER_H_
#define SENDING_MANAGER_H_

#include "defs.h"
#include "../mdc_messages.h"
#include "../common/net_end_point.h"

class ControlManager
{
private:
	
public:
	ControlManager(){}
	void handle_LIST(const NetEndPoint& sender, const MDCMessageList& msg);
	//void handle_ALST(const NetEndPoint& sender, const MDCMessageAlst& msg);
	void handle_SREQ(const NetEndPoint& sender, const MDCMessageSreq& msg);
	//void handle_ASRQ(const NetEndPoint& sender, const MDCMessageAsrq& msg);
	void handle_SINF(const NetEndPoint& sender, const MDCMessageSinf& msg);
	//void handle_ASNF(const NetEndPoint& sender, const MDCMessageAsnf& msg);
	void handle_PEER(const NetEndPoint& sender, const MDCMessagePeer& msg);
	//void handle_APER(const NetEndPoint& sender, const MDCMessageAper& msg);
	//void handle_KALV(const NetEndPoint& sender, const MDCMessageKalv& msg);
	//void handle_PARM(const NetEndPoint& sender, const MDCMessageParm& msg);
	
	void handle_ALST(const NetEndPoint& sender, const MDCMessageAlst& msg);
	void handle_APER(const NetEndPoint& sender, const MDCMessageAper& msg);
	void handle_ASNF(const NetEndPoint& sender, const MDCMessageAsnf& msg);
};

#endif /*SENDING_MANAGER_H_*/
