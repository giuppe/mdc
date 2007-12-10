
#include "defs.h"
#include "mdc_message_asrq.h"
#include <cstring>
#include <cstdlib>

void MDCMessageAsrq::set_hash(string hash)
{
	set_parameter_part("h", hash);
}
	
string MDCMessageAsrq::get_hash() const
{
	return get_parameter_part("h");
}
	
void MDCMessageAsrq::set_flow_id(Uint8 flow_id)
{
	char* buffer = new char[255];
	sprintf(buffer, "%d", flow_id);
	set_parameter_part("f", string(buffer));
	delete [] buffer;
}
	
Uint8 MDCMessageAsrq::get_flow_id() const
{
	return (Uint8) atoi(get_parameter_part("f").c_str());
}
	
void MDCMessageAsrq::set_sequence_begin(Uint32 sequence_begin)
{
	char* buffer = new char[255];
	sprintf(buffer, "%d", sequence_begin);
	set_parameter_part("sb", string(buffer));
	delete []buffer;
}
	
void MDCMessageAsrq::set_sequence_end(Uint32 sequence_end)
{
	char* buffer= new char[255];
	sprintf(buffer, "%d", sequence_end);
	set_parameter_part("se", string(buffer));
	delete [] buffer;
}
	
	Uint32 MDCMessageAsrq::get_sequence_begin() const
	{
		return (Uint32) atoi(get_parameter_part("sb").c_str());
	}

	Uint32 MDCMessageAsrq::get_sequence_end() const
	{
		return (Uint32) atoi(get_parameter_part("se").c_str());
	}
