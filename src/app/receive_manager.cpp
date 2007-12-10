
#include "defs.h"
#include "receive_manager.h"
#include "receive_filter_list.h"
#include "stream_info_cache_manager.h"
#include "stream_repository.h"



void ReceiveManager::handle_ASRQ(const NetEndPoint& sender, const MDCMessageAsrq& msg)
{

	ReceiveFilterList::instance()->add(sender.get_ip(), msg.get_hash());
	string temp_name = StreamInfoCacheManager::instance()->get_name(msg.get_hash());
	
	if(temp_name=="")
	{
		LOG_WARN("Stream name not found in cache, using stream_id as name");
		temp_name = msg.get_hash();
	}
	
	MDStreamInfo info = StreamInfoCacheManager::instance()->get_info(msg.get_hash());
	Uint8 flows_num= info.flows_number;
	Uint32 descriptors_num = info.descriptors_number;
	
	
	if((flows_num==0)||(descriptors_num==0))
	{
		LOG_ERROR("Stream info not found in cache, cannot create stream.");
		
	}
	else
	{
	
		LOG_INFO("Creating empty stream "<<temp_name);
		StreamRepository::instance()->create_stream(temp_name, msg.get_hash(), flows_num, descriptors_num);

	}	
}
