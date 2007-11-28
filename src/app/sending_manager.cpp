
#include "defs.h"
#include "sending_manager.h"
#include "../common/net_manager.h"
#include "stream_repository.h"
#include "../common/udp_message.h"
#include <cassert>

void SendingManager::handle_LIST(const NetEndPoint& sender, const MDCMessageList& msg)
{

	LOG_INFO("Requested name is "<<msg.get_name());
	std::vector<MDStream*> stream_list;

	stream_list = StreamRepository::instance()->find_by_name(msg.get_name());

	MDCMessageAlst response;

	for(Uint32 i=0; i<stream_list.size(); i++)
	{
		response.append_entry(stream_list[i]->get_name(),stream_list[i]->get_hash());

	}


	UDPMessage udp_msg;


	udp_msg.set_destination(NetEndPoint(sender.get_ip(), 5551));

	udp_msg.set_payload(response.serialize());

	udp_msg.send();

}


void SendingManager::handle_PEER(const NetEndPoint& sender, const MDCMessagePeer& msg)
{
	assert(!"This function is a stub");
#if 0

	LOG_INFO("Requested name is "<<msg.get_name());
	std::vector<MDStream*> stream_list;

	stream_list = StreamRepository::instance()->find_by_name(msg.get_name());

	MDCMessageAlst response;

	for(Uint32 i=0; i<stream_list.size(); i++)
	{
		response.append_entry(stream_list[i]->get_name(),stream_list[i]->get_hash());

	}


	UDPMessage udp_msg;


	udp_msg.set_destination(NetEndPoint(sender.get_ip(), 5551));

	udp_msg.set_payload(response.serialize());

	udp_msg.send();

#endif
}




void SendingManager::handle_SINF(const NetEndPoint& sender, const MDCMessageSinf& msg)
{
	assert(!"This function is a stub");
#if 0
	LOG_INFO("Requested name is "<<msg.get_name());
	std::vector<MDStream*> stream_list;

	stream_list = StreamRepository::instance()->find_by_name(msg.get_name());

	MDCMessageAlst response;

	for(Uint32 i=0; i<stream_list.size(); i++)
	{
		response.append_entry(stream_list[i]->get_name(),stream_list[i]->get_hash());

	}


	UDPMessage udp_msg;


	udp_msg.set_destination(NetEndPoint(sender.get_ip(), 5551));

	udp_msg.set_payload(response.serialize());

	udp_msg.send();
#endif
}




void SendingManager::handle_SREQ(const NetEndPoint& sender, const MDCMessageSreq& msg)
{
	assert(!"This function is a stub");
#if 0
	LOG_INFO("Requested name is "<<msg.get_name());
	std::vector<MDStream*> stream_list;

	stream_list = StreamRepository::instance()->find_by_name(msg.get_name());

	MDCMessageAlst response;

	for(Uint32 i=0; i<stream_list.size(); i++)
	{
		response.append_entry(stream_list[i]->get_name(),stream_list[i]->get_hash());

	}


	UDPMessage udp_msg;


	udp_msg.set_destination(NetEndPoint(sender.get_ip(), 5551));

	udp_msg.set_payload(response.serialize());

	udp_msg.send();
#endif
}





