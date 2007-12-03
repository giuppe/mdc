
#include "defs.h"
#include "descriptors_send_list.h"


bool DescriptorsSendList::pop_front(DescriptorToSend& desc_send)
{
	if(!m_list.empty())
	{
		desc_send = m_list.front();
		m_list.pop_front();
		return true;
	}
	return false;
	
}

void DescriptorsSendList::push_back(NetEndPoint dest, DescriptorId desc)
{
	DescriptorToSend desc_send;
	desc_send.desc_id = desc;
	desc_send.dest = dest;
	m_list.push_back(desc_send);
}






DescriptorsSendList* DescriptorsSendList::_instance = 0;

DescriptorsSendList* DescriptorsSendList::instance()
{
	if(_instance==0)
	{
		_instance=new DescriptorsSendList();
	}
	return _instance;
}