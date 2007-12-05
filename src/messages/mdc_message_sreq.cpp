
#include "defs.h"
#include "mdc_message_sreq.h"
#include <cstring>
#include <cstdlib>

void MDCMessageSreq::set_stream_id(std::string stream_id)
{
	set_parameter_part("h", stream_id);
}
	
std::string MDCMessageSreq::get_stream_id() const
{
	return get_parameter_part("h");
}
	
void MDCMessageSreq::set_flow_id(Uint8 flow_id)
{
	char* buffer = new char[255];
	sprintf(buffer, "%d", flow_id);
	set_parameter_part("f", std::string(buffer));
	delete [] buffer;
}
	
Uint8 MDCMessageSreq::get_flow_id() const
{
	return (Uint8) atoi(get_parameter_part("f").c_str());
}
	
void MDCMessageSreq::set_sequence_begin(Uint32 sequence_begin)
{
	char* buffer = new char[255];
	sprintf(buffer, "%d", sequence_begin);
	set_parameter_part("sb", std::string(buffer));
	delete []buffer;
}
	
void MDCMessageSreq::set_sequence_end(Uint32 sequence_end)
{
	char* buffer= new char[255];
	sprintf(buffer, "%d", sequence_end);
	set_parameter_part("se", std::string(buffer));
	delete [] buffer;
}
	
	Uint32 MDCMessageSreq::get_sequence_begin() const
	{
		return (Uint32) atoi(get_parameter_part("sb").c_str());
	}

	Uint32 MDCMessageSreq::get_sequence_end() const
	{
		return (Uint32) atoi(get_parameter_part("se").c_str());
	}
