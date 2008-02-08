
#ifndef PEER_INFO_CACHE_MANAGER_H_
#define PEER_INFO_CACHE_MANAGER_H_


#include "defs.h"
#include <vector>
#include "../common/net_end_point.h"

	struct PeerInfoEntry
	{
		NetEndPoint peer; 
		 
		PeerInfoEntry(){}
	};

typedef vector<PeerInfoEntry> PeerList;
//#include "../codecs/mdc/md_stream.h"

class PeerInfoCacheManager
{
private:


	
	map<string, PeerInfoEntry> m_stream_names;
	
public:
	
	void add_peer(string ip_address, NetEndPoint peer);

	PeerList& get_peers();
		
	// begin Singleton stuff

private:

static PeerInfoCacheManager* _instance;

protected:

PeerInfoCacheManager(){};
~PeerInfoCacheManager(){}

public:

static PeerInfoCacheManager* instance();

// end Singleton stuff

};


#endif /*PEER_INFO_CACHE_MANAGER_H_*/
