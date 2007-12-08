
#include "defs.h"
#include "application.h"

#include <iostream>

#include "common/config/commandline_configuration.h"
#include "app/app_configuration.h"
#include <cstdlib>
#include "defs.h"
#include "common/scheduler.h"
#include "codecs/codec_registry.h"
#include "codecs/mdc/md_stream.h"
#include "codecs/stream_factory.h"
#include "app/site_manager.h"
#include "server_action.h"
#include "client_test_action.h"
#include "app/sender_action.h"
#include "app/receiver.h"


void Application::print_usage()
{
	cout << "Multiple Description Codec\n\n";
	cout << "Use: mdc <parameters>\n\n";
	cout << "\t<parameters> ::= <action> {<code> | <decode>} <input> <output> <codec> [flows] [payload]\n\n";
	cout << "\t--input \t input filename.\n";
	cout << "\t--output \t output filename.\n";
	cout << "\t--code \t\t activate coding from input file to output MDC file.\n";
	cout << "\t--decode \t activate decoding from input MDC file to output file.\n";
	cout << "\t--codec \t select codec type to use for coding input file.\n";
	cout << "\t--flows \t number of output coded flows (from 1 to 64), DEFAULT 2.\n";
	cout << "\t--payload \t preferred payload size of each descriptor (from 25 to 55000 bytes for text), DEFAULT 1000.\n";
	cout << "\t--help \t\t show this help page.\n\n";
	cout << "Examples:\n";
	cout << "  mdc --input input_file.txt --codec text --code --flows 4 --payload 2000 --output output_file.mdc.\n";
	cout << "  mdc --input input_file.mdc --codec text --decode --output output_file.txt.\n\n";
	cout << "---------------------------------------------------------------\n\n";
}


void Application::init_all()
{
	SDL_Init(SDL_INIT_TIMER);
	LogManager::instance()->init(true, "./mdc_log.txt");
	NetManager::instance()->init();
	SDL_Delay(1000);
	CodecRegistry *codecReg = CodecRegistry::instance();
	codecReg->init();
	AppConfiguration::instance()->init();
}

int Application::main(int argc, char** argv) 
{
	cout<<"\nMultiple Description Codec v0.1\n";

	init_all();
	m_cli_config = new AppCliConfiguration();
	m_cli_config->init(argc, argv);

	if (m_cli_config->get_is_help()) 
	{
		print_usage();
		return 0;
	}
	
	if (m_cli_config->get_is_converter()) 
	{
		start_coder();
	}
	else 
	{

		start_scheduler();

	}

	return 0;
}

void Application::start_coder()
{
	string output_filename = m_cli_config->get_output_file();
	string input_filename = m_cli_config->get_input_file();
	string codec_name = m_cli_config->get_codec();
	Uint32 flows_number = m_cli_config->get_flows_number();
	Uint32 payload_size = m_cli_config->get_payload_size();
	
	if (input_filename=="") {
		cout<<"Input file parameter is missing.\n\n";
		return;
	}
	else {
		if (codec_name=="") {
			cout<<"Codec name parameter is missing.\n\n";
			return;
		}
		else {
			if (output_filename=="") {
				cout<<"Output file parameter is missing.\n\n";
				return;
			}
			else stream_converter(output_filename, input_filename, codec_name, flows_number, payload_size);
		}
	}
}

void Application::start_scheduler()
{
	Scheduler* sched = new Scheduler();

	ClientTestAction* client = new ClientTestAction();
	client->init("192.168.0.130", "192.168.0.108");
	SiteManager* site_manager = new SiteManager();
	Receiver* receiver = new Receiver();
	SenderAction* sender_action = new SenderAction();
	sender_action->set_maximum_time(1500);
	sched->add_action(sender_action);
	sched->add_action(site_manager);
	sched->add_action(receiver);

	sched->add_action(client);
	site_manager->start();
	sender_action->start();
	receiver->start();

	if(m_cli_config->get_is_daemon())
	{
		DEBUG_OUT("Starting daemon mode");
		while (1)
		{
			sched->execute_all();
			SDL_Delay(100);
		}

	}
	else
	{
		client->start();
		while (!client->is_action_exited()) 
		{
			sched->execute_all();
			SDL_Delay(100);
		}

	}
	delete site_manager;
	delete receiver;
	delete client;
	delete sender_action;
	delete sched;
}

void Application::deinit_all() {

	AppConfiguration::instance()->deinit();
	CodecRegistry::instance()->deinit();
	NetManager::instance()->deinit();
	LogManager::instance()->deinit();
}

void Application::stream_converter(string output_filename, string input_filename, string codec_name, Uint32 flows_number, Uint32 payload_size) {
	bool is_coding = m_cli_config->get_is_coding();
	bool is_decoding = m_cli_config->get_is_decoding();
	
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

Application::~Application()
{
	deinit_all();
	delete m_cli_config;
}

