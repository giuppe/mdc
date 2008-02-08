
#ifndef APP_CLI_CONFIGURATION_
#define APP_CLI_CONFIGURATION_

#include "defs.h"
#include "common/config/commandline_configuration.h"

class AppCliConfiguration : public CommandlineConfiguration
{
public:
	AppCliConfiguration(){};
	
	bool get_is_help();
	
	bool get_is_daemon();
	
	bool get_is_converter();
	
	bool get_is_coding();
	
	bool get_is_decoding();
	
	string get_input_file();
	
	string get_output_file();
	
	string get_codec();
	
	Uint32 get_flows_number();
	
	Uint32 get_payload_size();
	string get_address();
};

#endif /*APP_CLI_CONFIGURATION_*/
