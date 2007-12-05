
#include "defs.h"
#include "receive_manager.h"
#include "receive_filter_list.h"



void ReceiveManager::handle_ASRQ(const NetEndPoint& sender, const MDCMessageAsrq& msg)
{

	ReceiveFilterList::instance()->add(sender.get_ip(), msg.get_hash());


}
