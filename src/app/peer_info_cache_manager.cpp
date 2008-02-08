
#include "defs.h"
#include "peer_info_cache_manager.h"
#include <vector>




vector<PeerInfoEntry>& PeerInfoCacheManager::get_peers()
{

	PeerList* result = new PeerList();
	
	map<string, PeerInfoEntry>::const_iterator it;

	it = m_stream_names.begin();

	while(it!=m_stream_names.end())
	{
		PeerInfoEntry p;
		p.peer = it->second.peer;
		result->push_back(p);

	}

	return *result;		
}

void PeerInfoCacheManager::add_peer(string ip_address, NetEndPoint peer)
{
	m_stream_names[ip_address].peer= peer;
}
