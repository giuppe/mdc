
#include "defs.h"
#include "control_manager.h"
#include "../common/net_manager.h"
#include "stream_repository.h"
#include "../common/udp_message.h"
#include "descriptors_send_list.h"
#include "client_manager.h"
#include <cassert>

void ControlManager::handle_LIST(const NetEndPoint& sender, const MDCMessageList& msg)
{

	LOG_INFO("Requested name is "<<msg.get_name());
	std::vector<MDStream*> stream_list;

	stream_list = StreamRepository::instance()->find_by_name(msg.get_name());

	MDCMessageAlst response;

	for(Uint32 i=0; i<stream_list.size(); i++)
	{
		response.append_entry(StreamRepository::instance()->get_name_by_id(stream_list[i]->get_stream_id()),stream_list[i]->get_stream_id());

	}


	UDPMessage udp_msg;

	//FIXME destination port is embedded on code, to resolve with peer manager
	udp_msg.set_destination(NetEndPoint(sender.get_ip(), 5551));

	udp_msg.set_payload(response.serialize());

	udp_msg.send();

}


void ControlManager::handle_PEER(const NetEndPoint& sender, const MDCMessagePeer& msg)
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




void ControlManager::handle_SINF(const NetEndPoint& sender, const MDCMessageSinf& msg)
{
	StreamRepository* repo = StreamRepository::instance();
	MDStream* stream;
	
	if(repo->get_by_stream_id(msg.get_stream_id(), stream)==true)
	{
		LOG_INFO("getting info for "<<msg.get_stream_id());
		MDStreamInfo info =	stream->get_info();
		MDCMessageAsnf response;
		response.set_stream_id(info.stream_id);
		response.set_flows_number(info.flows_number);
		response.set_descriptors_number(info.descriptors_number);
		UDPMessage udp_msg;

			//FIXME destination port is embedded on code, to resolve with peer manager
			udp_msg.set_destination(NetEndPoint(sender.get_ip(), 5551));

			udp_msg.set_payload(response.serialize());

			udp_msg.send();
		
	}
	else
	{
		LOG_ERROR("Cannot get stream from stream id "<<msg.get_stream_id());
	}
	

}




void ControlManager::handle_SREQ(const NetEndPoint& sender, const MDCMessageSreq& msg)
{

	NetEndPoint destination_data(sender.get_ip(), 5552);
	NetEndPoint destination_control(sender.get_ip(), 5551);
		

	DescriptorId descriptor_id;
	
	std::string hash = msg.get_stream_id();
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


void ControlManager::handle_ALST(const NetEndPoint& sender, const MDCMessageAlst& msg)
{
	Uint32 entries_num = msg.get_num_rows();


	
	std::vector<SearchEntry> m_last_search;
	
	if(entries_num>0)
	{
		m_last_search.clear();
		m_last_search.resize(entries_num);

		for(Uint32 i=0; i<entries_num; i++)
		{
			m_last_search[i].set_name(msg.get_entry_name(i));
			m_last_search[i].set_stream_id(msg.get_entry_hash(i));
		}
		ClientManager::instance()->set_last_search(m_last_search);
	}

}

void ControlManager::handle_APER(const NetEndPoint& sender, const MDCMessageAper& msg)
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


void ControlManager::handle_ASNF(const NetEndPoint& sender, const MDCMessageAsnf& msg)
{
	LOG_INFO("Received ASNF for stream "<<msg.get_stream_id());
	MDStreamInfo m_last_stream_info;
	m_last_stream_info.stream_id = msg.get_stream_id();
	m_last_stream_info.flows_number = msg.get_flows_number();
	m_last_stream_info.descriptors_number = msg.get_descriptors_number();
	ClientManager::instance()->set_last_stream_info(m_last_stream_info);
	
}



