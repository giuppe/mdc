//============================================================================
// Name        : mdc.cpp
// Author      : Giuseppe D'Aqui'
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "common/net_manager.h"
#include "common/data_chunk.h"
#include "common/config/commandline_configuration.h"
#include <cstdlib>
#include "defs.h"
#include <SDL/SDL.h>
#include "common/scheduler.h"
#include "codecs/codec_registry.h"
#include "codecs/md_stream.h"
#include "codecs/stream_factory.h"
#include "server_action.h"
#include "client_test_action.h"

using namespace std;

void deinit_all();

void stream_converter(AbstractConfiguration*);

int main(int argc, char** argv) {
	std::cout<<"Multiple Description Codec v0.1";
	atexit(deinit_all);
	SDL_Init(SDL_INIT_TIMER);
	LogManager::instance()->init(true, "./mdc_log.txt");
	NetManager::instance()->init();
	SDL_Delay(1000);

	CodecRegistry* codecReg = CodecRegistry::instance();
	codecReg->init();
	
	AbstractConfiguration* config = new CommandlineConfiguration(argc, argv);
	bool get_help = false;
	bool call_convert1 = false;
	bool call_convert2 = false;
	config->get_bool("", "code", call_convert1);
	config->get_bool("", "decode", call_convert2);
	config->get_bool("", "help", get_help);
	if (get_help) {
		std::cout<<"Multiple Description Codec\n";
		std::cout<<"Uso: mdc [OPZIONE]\n";
		cout<<"\t--input \t input file name and path.\n";
		cout<<"\t--output \t output file name and path.\n";
		cout<<"\t--code \t\t code input file to output MDC file.\n";
		cout<<"\t--decode \t decode input MDC file to output file.\n";
		cout<<"\t--codec \t select codec type to use for coding input file.\n";
		cout<<"\t--flows \t number of output coded flows.\n";
		cout<<"\t--payload \t preferred payload size of each descriptor.\n";
		cout<<"\t--help \t show this help page.\n";
		return 0;
	}
	if((call_convert1==true)||(call_convert2==true))
	{
		stream_converter(config);
	}
	else
	{
	Scheduler* sched = new Scheduler();
	ServerAction* server = new ServerAction();
	
	ClientTestAction* client = new ClientTestAction();
	
	
	sched->add_action(server);
	
	sched->add_action(client);
	
	server->start();
	
	client->start();
	
	Uint32 times = 100;
	while(--times != 0)
	{
		sched->execute_all();
		SDL_Delay(100);
	}
	
	delete server;
	delete client;
	delete sched;
	}
	delete config;
	return 0;
}

void deinit_all() {
	CodecRegistry::instance()->deinit();
	NetManager::instance()->deinit();
	LogManager::instance()->deinit();
}


void stream_converter(AbstractConfiguration* config)
{
	std::string output_filename, input_filename, codec_name;
	bool is_coding = false;
	bool is_decoding = false;
	config->get_string("","output", output_filename);
	config->get_string("","input", input_filename);
	config->get_string("","codec", codec_name);
	config->get_bool("","code", is_coding);
	config->get_bool("","decode", is_decoding);
	DEBUG_OUT("converting "<<input_filename<<" to "<<output_filename<<"\n");
		DEBUG_OUT("\t using "<<codec_name<<" as codec");
		CodecRegistry* codecReg = CodecRegistry::instance();
		AbstractMDCodec* codec;
		bool exists_codec = false;
		exists_codec = codecReg->get_codec(codec_name, codec);
		if(!exists_codec)
		{
			DEBUG_OUT("Unable to find codec "<<codec_name);
			exit(1);
		}
		AbstractStream* stream = StreamFactory::create_stream(codec_name);
		codecReg->get_codec(codec_name, codec);
		MDStream mdstream;
	if(is_coding == true)
	{
		stream->load_from_disk(input_filename);
		codec->code(stream, &mdstream);
		mdstream.save_to_disk(output_filename);
				
	}
	else if(is_decoding == true)
	{
		mdstream.load_from_disk(input_filename);
		codec->decode(&mdstream, stream);
		stream->save_to_disk(output_filename);
						
	}
	delete stream;
}
