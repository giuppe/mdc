
#include "defs.h"
#include "sending_manager.h"
#include "../common/net_manager.h"
#include "stream_repository.h"
#include "../common/udp_message.h"
#include "descriptors_send_list.h"
#include <cassert>

void SendingManager::handle_LIST(const NetEndPoint& sender, const MDCMessageList& msg)
{

	LOG_INFO("Requested name is "<<msg.get_name());
	std::vector<MDStream*> stream_list;

	stream_list = StreamRepository::instance()->find_by_name(msg.get_name());

	MDCMessageAlst response;

	for(Uint32 i=0; i<stream_list.size(); i++)
	{
		response.append_entry(stream_list[i]->get_name(),stream_list[i]->get_stream_id());

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

	NetEndPoint destination_data(sender.get_ip(), 5552);
	NetEndPoint destination_control(sender.get_ip(), 5551);
		

	DescriptorId descriptor_id;
	
	std::string hash = msg.get_hash();
	Uint8 flow_id = msg.get_flow_id();
	
	
	Uint32 seq_start = msg.get_sequence_begin();
	Uint32 seq_end = msg.get_sequence_end();
	
	for(Uint32 i= seq_start; i<=seq_end; i++)
	{
		descriptor_id.hash = hash;
		descriptor_id.flow_id = flow_id;
		descriptor_id.sequence_id = i;
			
		DescriptorsSendList::instance()->push_back(destination_data, descriptor_id);
	}
	// FIXME: here we should check if we have those descriptors, before sending ASRQ
	
	MDCMessageAsrq response;
	response.set_hash(hash);
	response.set_flow_id(flow_id);
	response.set_sequence_begin(seq_start);
	response.set_sequence_end(seq_end);
	
	UDPMessage udp_msg;
	udp_msg.set_destination(destination_control);
	udp_msg.set_payload(response.serialize());
	
	udp_msg.send();
	
	
}





