
#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "defs.h"
#include <string>
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
	
	void stream_converter(std::string, std::string, std::string, Uint32, Uint32);


private:
    void print_usage();
    void init_all();
    void start_scheduler();
    void start_coder();
};

#endif /*APPLICATION_H_*/
