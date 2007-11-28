
#ifndef UDP_MESSAGE_H_
#define UDP_MESSAGE_H_

#include "defs.h"
#include "net_end_point.h"
#include "data_chunk.h"


class UDPMessage
{
private:
	NetEndPoint m_destination;
	
	DataChunk m_payload;
	
public:
	UDPMessage();
	
	void set_destination(NetEndPoint destination);
	
	NetEndPoint get_destination() const;
	
	void set_payload(const DataChunk& data);
	
	void send();
	
	
};

#endif /*UDP_MESSAGE_H_*/
