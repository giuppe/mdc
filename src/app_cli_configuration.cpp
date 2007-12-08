
#include "defs.h"
#include "app_cli_configuration.h"



bool AppCliConfiguration::get_is_converter()
{
	bool call_convert1 = false;
	bool call_convert2 = false;
	get_bool("", "code", call_convert1);
	get_bool("", "decode", call_convert2);
	return (call_convert1 || call_convert2);
}


bool AppCliConfiguration::get_is_coding()
{
	bool is_coding = false;

	get_bool("", "code", is_coding);
	return is_coding;
}

bool AppCliConfiguration::get_is_decoding()
{
	bool is_decoding = false;
	get_bool("", "decode", is_decoding);
	return is_decoding;
}

bool AppCliConfiguration::get_is_help()
{
	bool get_help = false;
	get_bool("", "help", get_help);
	return get_help;
}


bool AppCliConfiguration::get_is_daemon()
{
	bool start_daemon=false;
	get_bool("", "daemon", start_daemon);
	return start_daemon;
}

string AppCliConfiguration::get_input_file()
{
	string input_filename;
	input_filename.resize(0);
	get_string("", "input", input_filename);
	if ((input_filename=="true") || (input_filename=="false") || (input_filename==""))
	{
		return "";
	}
	else
	{
		return input_filename;
	}

}

string AppCliConfiguration::get_output_file()
{
	string output_filename;

	output_filename.resize(0);

	get_string("", "output", output_filename);

	if((output_filename=="true") || (output_filename=="false") || (output_filename==""))
	{
		return "";
	}
	else
	{
		return output_filename;
	}
}

string AppCliConfiguration::get_codec()
{
	string codec_name;
	codec_name.resize(0);
	get_string("", "codec", codec_name);
	if ((codec_name=="true") || (codec_name=="false") || (codec_name==""))
	{
		return "";
	}
	else
	{
		return codec_name;
	}

}

Uint32 AppCliConfiguration::get_flows_number()
{
	Uint32 flows_number = 0;

	get_int("", "flows", flows_number);
	return flows_number;
}

Uint32 AppCliConfiguration::get_payload_size()
{

	Uint32 payload_size = 0;

	get_int("", "payload", payload_size);

	return payload_size;
}
