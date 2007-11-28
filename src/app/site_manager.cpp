
#include "defs.h"
#include "site_manager.h"
#include <cassert>
#include "../mdc_messages.h"
#include "../common/net_manager.h"
#include "stream_repository.h"
#include "../common/net_end_point.h"

SiteManager::SiteManager()
{
	m_listening_socket = NetManager::instance()->create_UDP_listen_socket("localhost", 5551);
	LOG_INFO("Listening on port 5551 for control packets.");
	
	StreamRepository::instance()->init("/home/giuppe/repo_mdc");
	
}



void SiteManager::action()
{
	DataChunk received;

	Uint32 sender_address;

	Uint16 sender_port;

	if(NetManager::instance()->receive_data(m_listening_socket, received, sender_address, sender_port))
	{

		MDCMessage msg;
		msg.deserialize(received);
		LOG_INFO("Received packet, of type: "<<msg.get_type_string());

		if(strcmp(msg.get_type_string(), "LIST")==0)
		{
			MDCMessageList msg_list;
			msg_list.deserialize(received);

			m_sending_manager.handle_LIST(NetEndPoint(sender_address, sender_port), msg_list);
			
		}
		else if(strcmp(msg.get_type_string(), "PEER")==0)
		{
			MDCMessagePeer msg_peer;
			msg_peer.deserialize(received);
			m_sending_manager.handle_PEER(NetEndPoint(sender_address, sender_port), msg_peer);
		}
		else if(strcmp(msg.get_type_string(), "SINF")==0)
		{
			MDCMessageSinf msg_sinf;
			msg_sinf.deserialize(received);
			m_sending_manager.handle_SINF(NetEndPoint(sender_address, sender_port), msg_sinf);
		}
		else if(strcmp(msg.get_type_string(), "SREQ")==0)
		{
			MDCMessageSreq msg_sreq;
			msg_sreq.deserialize(received);
			m_sending_manager.handle_SREQ(NetEndPoint(sender_address, sender_port), msg_sreq);
		}
		else if(strcmp(msg.get_type_string(), "APER")==0)
		{
			MDCMessageAper msg_aper;
			msg_aper.deserialize(received);
			assert(!"Unable to handle APER messages: function not implemented");
		}
		else if(strcmp(msg.get_type_string(), "ASRQ")==0)
		{
			MDCMessageAsrq msg_asrq;
			msg_asrq.deserialize(received);
			m_receive_manager.handle_ASRQ(NetEndPoint(sender_address, sender_port), msg_asrq);
		}
		else if(strcmp(msg.get_type_string(), "ASNF")==0)
		{
			MDCMessageAsnf msg_asnf;
			msg_asnf.deserialize(received);
			m_client_manager.handle_ASNF(NetEndPoint(sender_address, sender_port), msg_asnf);
		}
		else if(strcmp(msg.get_type_string(), "ALST")==0)
		{
			MDCMessageAlst msg_alst;
			msg_alst.deserialize(received);
			m_client_manager.handle_ALST(NetEndPoint(sender_address, sender_port), msg_alst);
		}
		else if(strcmp(msg.get_type_string(), "KALV")==0)
		{
			MDCMessageKalv msg_aper;
			msg_aper.deserialize(received);
			LOG_ERROR("Unable to handle KALV messages: function not implemented");
		}
		else if(strcmp(msg.get_type_string(), "PARM")==0)
		{
			MDCMessageParm msg_aper;
			msg_aper.deserialize(received);
			LOG_ERROR("Unable to handle PARM messages: function not implemented");
		}
	}

}
