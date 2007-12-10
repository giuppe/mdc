
#ifndef CLIENT_MANAGER_H_
#define CLIENT_MANAGER_H_

#include "defs.h"
#include "../mdc_messages.h"
#include "../common/net_end_point.h"
#include "../codecs/mdc/md_stream.h"
#include <string>
#include <vector>

class SearchEntry
{
private:
	string m_name;
	string m_stream_id;
public:
	SearchEntry():m_name(""),m_stream_id(""){}
	
	string get_name(){return m_name;}
	
	string get_stream_id(){return m_stream_id;}
	
	void set_name(string name){m_name = name;}
	
	void set_stream_id(string stream_id){m_stream_id = stream_id;}
		
	
};

class ClientManager
{
private:
	vector<SearchEntry> m_last_search;
	MDStreamInfo m_last_stream_info;
public:

	
	void search(NetEndPoint peer, string stream_name) const;
	
	vector<SearchEntry> get_last_search() const;
	
	void request_stream_info(NetEndPoint peer, string stream_id) const;
	
	MDStreamInfo get_last_stream_info() const;
	
	void request_stream(NetEndPoint peer, string stream_id, Uint8 flow_id, Uint32 sequence_begin, Uint32 sequence_end) const;
	
	void deinit(){};
	
	void set_last_search(const vector<SearchEntry>& last_search);
	
	void set_last_stream_info(MDStreamInfo stream_info);
	
	// begin Singleton stuff

private:

static ClientManager* _instance;

protected:

	ClientManager(){};
~ClientManager(){deinit();}

public:

static ClientManager* instance();

// end Singleton stuff

		
};

#endif /*CLIENT_MANAGER_H_*/
