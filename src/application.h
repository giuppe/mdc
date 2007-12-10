
#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "defs.h"

#include "app_cli_configuration.h"

class Application
{
private:
	AppCliConfiguration* m_cli_config;
public:
	
	Application(){}
	
	~Application();
	
	int main(int argc, char** argv);
	
	void deinit_all();
	
	void stream_converter(string, string, string, Uint32, Uint32);


private:
    void print_usage();
    void init_all();
    void start_scheduler();
    void start_coder();
};

#endif /*APPLICATION_H_*/
