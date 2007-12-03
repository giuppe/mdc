#ifndef DESCRIPTORS_SEND_LIST_H_
#define DESCRIPTORS_SEND_LIST_H_

#include "defs.h"
#include "../common/net_end_point.h"
#include <list>

struct DescriptorId
{
	std::string hash;
	Uint8 flow_id;
	Uint32 sequence_id;
};

struct DescriptorToSend
{
	DescriptorId desc_id;
	NetEndPoint dest;
};

class DescriptorsSendList
{
private:
	std::list<DescriptorToSend> m_list;
public:
	void push_back(NetEndPoint dest, DescriptorId desc);
	bool pop_front(DescriptorToSend& desc_send);
	
	
	
	void deinit(){};
	
	
	
	// begin Singleton stuff

private:

static DescriptorsSendList* _instance;

protected:

	DescriptorsSendList(){};
~DescriptorsSendList(){deinit();}

public:

static DescriptorsSendList* instance();

// end Singleton stuff
	
};

#endif /*DESCRIPTORS_SEND_LIST_H_*/
