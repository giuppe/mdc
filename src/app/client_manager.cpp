
#include "defs.h"
#include "client_manager.h"
#include "../mdc_messages.h"
#include "../common/udp_message.h"





void ClientManager::search(NetEndPoint peer, string stream_name) const
{

	MDCMessageList msg;
	msg.set_name(stream_name);
	UDPMessage udp_msg;
	udp_msg.set_destination(peer);
	udp_msg.set_payload(msg.serialize());
	udp_msg.send();
	
}


void ClientManager::request_stream_info(NetEndPoint peer, string stream_id) const
{
	MDCMessageSinf msg;
	msg.set_stream_id(stream_id);
	UDPMessage udp_msg;
	udp_msg.set_destination(peer);
	udp_msg.set_payload(msg.serialize());
	udp_msg.send();
}

void ClientManager::request_stream(NetEndPoint peer, string stream_id, Uint8 flow_id, Uint32 sequence_begin, Uint32 sequence_end) const
{
	MDCMessageSreq msg;
	msg.set_stream_id(stream_id);
	msg.set_flow_id(flow_id);
	msg.set_sequence_begin(sequence_begin);
	msg.set_sequence_end(sequence_end);
	UDPMessage udp_msg;
	udp_msg.set_destination(peer);
	udp_msg.set_payload(msg.serialize());
	udp_msg.send();
}

void ClientManager::get_peer_of_peer(NetEndPoint peer) const
{
	MDCMessagePeer msg;
	UDPMessage udp_msg;
	udp_msg.set_destination(peer);
	udp_msg.set_payload(msg.serialize());
	udp_msg.send();
}



MDStreamInfo ClientManager::get_last_stream_info() const
{
	return m_last_stream_info;
}

vector<SearchEntry> ClientManager::get_last_search() const
{
	return m_last_search;
}

void ClientManager::set_last_search(const vector<SearchEntry>& last_search)
{
	m_last_search = last_search;
}

void ClientManager::set_last_stream_info(MDStreamInfo stream_info)
{
	m_last_stream_info = stream_info;
}


ClientManager* ClientManager::_instance = 0;

ClientManager* ClientManager::instance()
{
	if(_instance==0)
	{
		_instance=new ClientManager();
	}
	return _instance;
}



