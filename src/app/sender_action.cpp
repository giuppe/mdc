
#include "defs.h"
#include "sender_action.h"
#include "descriptors_send_list.h"
#include "stream_repository.h"
#include "../common/udp_message.h"
#include "../codecs/mdc/descriptor.h"


SenderAction::SenderAction()
{
	
}


void SenderAction::action()
{
	//iterate through a list of stuff to send, sending it
	
	DescriptorsSendList* send_list = DescriptorsSendList::instance();
	
	StreamRepository* stream_repo = StreamRepository::instance();
	
	DescriptorToSend desc_send;
	
	while((send_list->pop_front(desc_send))&&(!this->is_elapsed_maximum_time()))
	{
		NetEndPoint destination = desc_send.dest;
		DescriptorId desc_id = desc_send.desc_id;
		LOG_INFO("Trying to send descriptor stream_id="<<desc_id.hash);
		LOG_INFO("flow_id="<<desc_id.flow_id<<", sequence_id="<<desc_id.sequence_id);
		
		MDStream* chosen_stream;
		if(stream_repo->get_by_stream_id(desc_id.hash, chosen_stream))
		{
			
			Descriptor* chosen_descriptor;
			if(chosen_stream->get_descriptor(desc_id.flow_id, desc_id.sequence_id, chosen_descriptor))
			{
				LOG_INFO("Got Descriptor");
				UDPMessage msg;
				msg.set_destination(destination);
				msg.set_payload(chosen_descriptor->serialize());
				msg.send();
				LOG_INFO("Sent to "<<destination.get_ip());
			}
			else
			{
				LOG_WARN("Unable to open descriptor ("<<desc_id.flow_id<<", "<<desc_id.sequence_id<<")");
			}
		}
		else
		{
			LOG_WARN("Unable to open mdstream with hash "<<desc_id.hash);
		}
	}

	
	

}
