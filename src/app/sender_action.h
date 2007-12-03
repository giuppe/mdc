

#ifndef SENDER_H_
#define SENDER_H_

#include "defs.h"
#include "../common/action_timed.h"

class SenderAction : public ActionTimed
{
public:
	SenderAction();
	void action();
};

#endif /*SENDER_H_*/
