
#ifndef RECEIVER_H_
#define RECEIVER_H_

#include "defs.h"
#include "receive_filter_list.h"
#include "../common/action.h"

class Receiver : public Action
{
	
private:
	Uint32 m_listening_socket;
	void pre_action(){}
		
		void post_action(){}
public:
	Receiver();
	void action();
};

#endif /*RECEIVER_H_*/
