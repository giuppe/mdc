
#include "defs.h"
#include "site_manager.h"
#include <cassert>
#include "../mdc_messages.h"
#include "../common/net_manager.h"
#include "stream_repository.h"
#include "../common/net_end_point.h"
#include "app_configuration.h"

SiteManager::SiteManager()
{
	Uint16 control_port = AppConfiguration::instance()->get_control_port();
	m_listening_socket = NetManager::instance()->create_UDP_listen_socket("localhost", control_port);
	LOG_INFO("Listening on port "<<control_port<<" for control packets.");
	
	std::string repository_path = AppConfiguration::instance()->get_repository_path();
	LOG_INFO("Using "<<repository_path<<" as repository");
	StreamRepository::instance()->init(repository_path);
	
	
}



void SiteManager::action()
{
	DataChunk received;


	NetEndPoint sender;

	if(NetManager::instance()->receive_data(m_listening_socket, received, sender))
	{

		MDCMessage msg;
		msg.deserialize(received);
		LOG_INFO("Received packet, of type: "<<msg.get_type_string());

		if(strcmp(msg.get_type_string(), "LIST")==0)
		{
			MDCMessageList msg_list;
			msg_list.deserialize(received);

			m_sending_manager.handle_LIST(sender, msg_list);
			
		}
		else if(strcmp(msg.get_type_string(), "PEER")==0)
		{
			MDCMessagePeer msg_peer;
			msg_peer.deserialize(received);
			m_sending_manager.handle_PEER(sender, msg_peer);
		}
		else if(strcmp(msg.get_type_string(), "SINF")==0)
		{
			MDCMessageSinf msg_sinf;
			msg_sinf.deserialize(received);
			m_sending_manager.handle_SINF(sender, msg_sinf);
		}
		else if(strcmp(msg.get_type_string(), "SREQ")==0)
		{
			MDCMessageSreq msg_sreq;
			msg_sreq.deserialize(received);
			m_sending_manager.handle_SREQ(sender, msg_sreq);
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
			m_receive_manager.handle_ASRQ(sender, msg_asrq);
		}
		else if(strcmp(msg.get_type_string(), "ASNF")==0)
		{
			MDCMessageAsnf msg_asnf;
			msg_asnf.deserialize(received);
			m_sending_manager.handle_ASNF(sender, msg_asnf);
		}
		else if(strcmp(msg.get_type_string(), "ALST")==0)
		{
			MDCMessageAlst msg_alst;
			msg_alst.deserialize(received);
			m_sending_manager.handle_ALST(sender, msg_alst);
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
