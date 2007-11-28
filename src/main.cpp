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
#include "codecs/mdc/md_stream.h"
#include "codecs/stream_factory.h"
#include "app/site_manager.h"
#include "server_action.h"
#include "client_test_action.h"

using namespace std;

void deinit_all();
void stream_converter(AbstractConfiguration*, std::string, std::string, std::string, Uint32, Uint32);

int main(int argc, char** argv) {
	std::cout<<"\nMultiple Description Codec v0.1\n";
	atexit(deinit_all);
	SDL_Init(SDL_INIT_TIMER);
	LogManager::instance()->init(true, "./mdc_log.txt");
	NetManager::instance()->init();
	SDL_Delay(1000);
	CodecRegistry* codecReg = CodecRegistry::instance();
	codecReg->init();
	AbstractConfiguration* config = new CommandlineConfiguration(argc, argv);
	bool get_help = false;
	config->get_bool("", "help", get_help);
	if (get_help) {
		std::cout<<"Multiple Description Codec\n\n";
		std::cout<<"Use: mdc <parameters>\n\n";
		std::cout<<"\t<parameters> ::= <action> {<code> | <decode>} <input> <output> <codec> [flows] [payload]\n\n";
		std::cout<<"\t--input \t input filename.\n";
		std::cout<<"\t--output \t output filename.\n";
		std::cout<<"\t--code \t\t activate coding from input file to output MDC file.\n";
		std::cout<<"\t--decode \t activate decoding from input MDC file to output file.\n";
		std::cout<<"\t--codec \t select codec type to use for coding input file.\n";
		std::cout<<"\t--flows \t number of output coded flows (from 1 to 64), DEFAULT 2.\n";
		std::cout<<"\t--payload \t preferred payload size of each descriptor (from 25 to 55000 bytes for text), DEFAULT 1000.\n";
		std::cout<<"\t--help \t\t show this help page.\n\n";
		std::cout<<"Examples:\n";
		std::cout<<"  mdc --input input_file.txt --codec text --code --flows 4 --payload 2000 --output output_file.mdc.\n";
		std::cout<<"  mdc --input input_file.mdc --codec text --decode --output output_file.txt.\n\n";
		std::cout<<"---------------------------------------------------------------\n\n";
		return 0;
	}
	bool call_convert1 = false;
	bool call_convert2 = false;
	config->get_bool("", "code", call_convert1);
	config->get_bool("", "decode", call_convert2);
	if (call_convert1 || call_convert2) {
		std::string output_filename, input_filename, codec_name;
		Uint32 flows_number = 0;
		Uint32 payload_size = 0;
		output_filename.resize(0);
		input_filename.resize(0);
		codec_name.resize(0);
		config->get_string("", "output", output_filename);
		config->get_string("", "input", input_filename);
		config->get_string("", "codec", codec_name);
		config->get_int("", "flows", flows_number);
		config->get_int("", "payload", payload_size);
		if ((input_filename=="true") || (input_filename=="false") || (input_filename=="")) {
			std::cout<<"Input file parameter is missing.\n\n";
			return 0;
		}
		else {
			if ((codec_name=="true") || (codec_name=="false") || (codec_name=="")) {
				std::cout<<"Codec name parameter is missing.\n\n";
				return 0;
			}
			else {
				if ((output_filename=="true") || (output_filename=="false") || (output_filename=="")) {
					std::cout<<"Output file parameter is missing.\n\n";
					return 0;
				}
				else stream_converter(config, output_filename, input_filename, codec_name, flows_number, payload_size);
			}
		}
	}
	else {
		std::cout<<"\nAction parameter is missing, daemon start.\n\n";
		Scheduler* sched = new Scheduler();
		ServerAction* server = new ServerAction();
		ClientTestAction* client = new ClientTestAction();
		SiteManager* site_manager = new SiteManager();
		sched->add_action(site_manager);
		sched->add_action(server);
		sched->add_action(client);
		site_manager->start();
		//server->start();
		//client->start();
		Uint32 times = 10000;
		while (--times != 0) {
			sched->execute_all();
			SDL_Delay(100);
		}
		delete site_manager;
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

void stream_converter(AbstractConfiguration* config, std::string output_filename, std::string input_filename, std::string codec_name, Uint32 flows_number, Uint32 payload_size) {
	bool is_coding = false;
	bool is_decoding = false;
	config->get_bool("", "code", is_coding);
	config->get_bool("", "decode", is_decoding);
	DEBUG_OUT("converting "<<input_filename<<" to "<<output_filename<<"\n");
		DEBUG_OUT("\t using "<<codec_name<<" as codec");
		CodecRegistry* codecReg = CodecRegistry::instance();
		AbstractMDCodec* codec;
		bool exists_codec = false;
		exists_codec = codecReg->get_codec(codec_name, codec);
		if (!exists_codec) {
			DEBUG_OUT("Unable to find codec "<<codec_name);
			exit(1);
		}
		AbstractStream* stream = StreamFactory::create_stream(codec_name);
		codecReg->get_codec(codec_name, codec);
		MDStream mdstream;
	if (is_coding) {
		stream->load_from_disk(input_filename);
		if ((flows_number>0) && (flows_number<65))
			codec->set_flows_number(flows_number);
		if ((payload_size>1) && (payload_size<64000))
			codec->set_preferred_payload_size(payload_size);
		codec->code(stream, &mdstream);
		mdstream.save_to_disk(output_filename);
	}
	else if (is_decoding) {
		mdstream.load_from_disk(input_filename);
		codec->decode(&mdstream, stream);
		stream->save_to_disk(output_filename);
	}
	delete stream;
}
