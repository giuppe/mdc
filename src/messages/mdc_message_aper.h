/***************************************************************************
                          mdc_message_aper.h  -  Insert description
                             -------------------
    begin                : Sep 12, 2007
    copyright          : (C) 2007 by Giuseppe D'Aqui'
    email                : giuseppe.da@gmail.com
 ***************************************************************************/

/***************************************************************************
 *                                                                                                                 
 *   This program is free software; you can redistribute it and/or modify  
 *   it under the terms of the GNU General Public License, Version 2,        
 *   as published by the Free Software Foundation.                                  
 *                                                                                                                 
 ***************************************************************************/

#include "defs.h"
#include "mdc_message_vector.h"
#include "../common/net_end_point.h"
#include <cmath>



#ifndef MDC_MESSAGE_APER_H_
#define MDC_MESSAGE_APER_H_

class MDCMessageAper : public MDCMessageVector
{

public:
	
	MDCMessageAper()
	{
		this->init_header();

		this->set_type_string("APER");
		
		

	}
	
	Uint32 get_num_entries() const {return get_num_rows();}
	
	void append_entry(NetEndPoint peer)
	{
		
		string entry = "a=";
		entry += peer.get_ip();
		entry += ";&";
		entry += "p=";
		entry += peer.get_port();
		entry += ";";
		m_rows.push_back(entry);
	}
	
	NetEndPoint get_peer(Uint32 num_entry) const
	{
		if(num_entry>m_rows.size())
		{
			LOG_ERROR("Trying to get a parameter outside range.")
			return NetEndPoint();
		}
		
		string ip = get_parameter_part(num_entry, "a");
		
		Uint16 port = atoi(get_parameter_part(num_entry, "p").c_str());
		
		return NetEndPoint(ip, port);
	}
	

	
	
	
};

#endif /*MDC_MESSAGE_APER_H_*/
