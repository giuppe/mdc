
#ifndef RECEIVER_H_
#define RECEIVER_H_

#include "defs.h"
#include "receive_filter_list.h"
#include "../common/action.h"

class Receiver : public Action
{
public:
	Receiver(){}
	void action();
};

#endif /*RECEIVER_H_*/
