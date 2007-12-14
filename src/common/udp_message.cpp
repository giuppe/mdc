
#include "defs.h"
#include "udp_message.h"
#include "net_manager.h"


NetEndPoint UDPMessage::get_destination() const
{
	return m_destination;
}



void UDPMessage::set_destination(NetEndPoint destination)
{
	m_destination = destination;
}



void UDPMessage::send()
{
	if((m_destination.is_valid())&&(m_payload.get_lenght()>0))
	{
		LOG_INFO("Sending UDP packet to "<<m_destination.get_ip());
		NetManager::instance()->send_data(m_destination, m_payload);
	}
	else
	{
		LOG_ERROR("Cannot send "<<m_payload.get_lenght()<<" byte to "<<m_destination.get_ip()<<":"<<m_destination.get_port()<<".");	
	}
}

UDPMessage::UDPMessage()
{
	
}


void UDPMessage::set_payload(const MemDataChunk& data)
{
	m_payload.erase();
	m_payload+=&data;
}	


