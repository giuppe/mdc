
#include "defs.h"
#include "client_manager.h"


void ClientManager::handle_ALST(const NetEndPoint& sender, const MDCMessageAlst& msg)
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

void ClientManager::handle_APER(const NetEndPoint& sender, const MDCMessageAper& msg)
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


void ClientManager::handle_ASNF(const NetEndPoint& sender, const MDCMessageAsnf& msg)
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
