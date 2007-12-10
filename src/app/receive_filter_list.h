
#ifndef RECEIVE_FILTER_LIST_H_
#define RECEIVE_FILTER_LIST_H_

#include "defs.h"

#include <ctime>


class ReceiveEntry
{
	string m_ip;
	string m_hash;
		
public:
	
	ReceiveEntry(string ip, string hash):m_ip(ip),m_hash(hash){}
	
	bool operator==(const ReceiveEntry& r) const
	{
		return (m_ip==r.m_ip)&&(m_hash==r.m_hash);
	}
	
	bool operator<(const ReceiveEntry& r) const
	{
		return (m_ip<r.m_ip)&&(m_hash<r.m_hash);
	}
};


class ReceiveFilterList
{
private:
	map<ReceiveEntry, Uint64> m_list;
	
	Uint32 m_timeout;
	
public:
	
	bool exists(string ip, string hash);
	
	void add(string ip, string hash);
	
	void remove_outdated();
	
	void set_timeout(Uint32 timeout);
	
	void deinit(){}

	// begin Singleton stuff

private:

static ReceiveFilterList* _instance;

protected:

	ReceiveFilterList(){};
~ReceiveFilterList(){deinit();}

public:

static ReceiveFilterList* instance();

// end Singleton stuff

	
};

#endif /*RECEIVE_FILTER_LIST_H_*/
