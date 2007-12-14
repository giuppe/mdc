
#include "defs.h"
#include "receiver.h"
#include "stream_repository.h"
#include "../common/net_manager.h"
#include "../mdc_messages.h"
#include "../codecs/mdc/descriptor.h"
#include "app_configuration.h"
#include <cassert>

Receiver::Receiver()
{
	Uint16 data_port = AppConfiguration::instance()->get_data_port();
		m_listening_socket = NetManager::instance()->create_UDP_listen_socket("localhost", data_port);
		LOG_INFO("Listening on port "<<data_port<<" for data packets.");

	
}


void Receiver::action()
{
	StreamRepository* repo = StreamRepository::instance();
	ReceiveFilterList* filter_list = ReceiveFilterList::instance();
	

	MemDataChunk received;


	
	NetEndPoint sender;

	//-listen on port 5552

	if(NetManager::instance()->receive_data(m_listening_socket, received, sender))
	{

		MDCMessage msg;
		msg.deserialize(&received);
		LOG_INFO("Received packet, of type: "<<msg.get_type_string());
		
		//-receive every descriptor
		if(strcmp(msg.get_type_string(), "DESC")==0)
		{
			Descriptor* curr_desc = new Descriptor();
			curr_desc->deserialize(&received);
			
			LOG_INFO("Descriptor ("<<curr_desc->get_flow_id()<<", "<<curr_desc->get_sequence_number()<<") for stream id "<<curr_desc->get_stream_id());
			//-filter every descriptor with the help of a list, filled with result of ASRQs
			
			if(filter_list->exists(sender.get_ip(), curr_desc->get_stream_id()))
			{
				//--if the new descriptor fits on these constraints, write it to disk
				MDStream* curr_stream;
				if(repo->get_by_stream_id(curr_desc->get_stream_id(), curr_stream))
				{
					curr_stream->set_descriptor(curr_desc);
				}
				else
				{
					LOG_WARN("Unable to find stream "<<curr_desc->get_stream_id()<<" in repository.");
		
				}
			}
			else
			{
				LOG_WARN("Received descriptor not present in filter list, discarding.");
			}
			
		}
		else
		{
			LOG_WARN("Received corrupted descriptor on data port, discarding.");
			
		}
	}

	
}
