
#ifndef NET_END_POINT_H_
#define NET_END_POINT_H_

#include "defs.h"

class NetEndPoint
{
private:
	Uint32 m_ip;
	Uint16 m_port;
	
public:
	
	NetEndPoint():m_ip(0),m_port(0){}
	
	NetEndPoint(Uint32 ip, Uint16 port):m_ip(ip), m_port(port){};
	
	Uint32 get_ip() const {return m_ip;}
	
	Uint16 get_port() const {return m_port;}
	
	bool is_valid() const {return (m_ip!=0)&&(m_port!=0);}
	
};

#endif /*NET_END_POINT_H_*/
