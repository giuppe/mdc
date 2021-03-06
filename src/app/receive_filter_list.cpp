#include "defs.h"

#include "receive_filter_list.h"

#include <cassert>

bool ReceiveFilterList::exists(string ip, string hash)
{
	map<ReceiveEntry, Uint64>::iterator iter= m_list.find(ReceiveEntry(ip, hash));

	if( iter != m_list.end() ) 
	{
		return true;
	}
	return false;
}




void ReceiveFilterList::add(string ip, string hash)
{
	Uint64 now = (Uint64) time(NULL);
	m_list.insert(make_pair(ReceiveEntry(ip, hash), now));
}




void ReceiveFilterList::remove_outdated()
{
	assert(!"This function is a stub.");
	
	Uint64 now = (Uint64) time(NULL);
	Uint64 outdated_time = now - m_timeout;
	
	map<ReceiveEntry, Uint64>::iterator iter;
	
	for(iter = m_list.begin(); iter!=m_list.end(); iter++)
	{
		if( iter->second < outdated_time ) 
		{
			m_list.erase(iter);
		}
	}
	
}



void ReceiveFilterList::set_timeout(Uint32 timeout)
{
	m_timeout = timeout;
}



ReceiveFilterList* ReceiveFilterList::_instance = 0;

ReceiveFilterList* ReceiveFilterList::instance()
{
	if(_instance==0)
	{
		_instance=new ReceiveFilterList();
	}
	return _instance;
}




