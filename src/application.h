
#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "defs.h"
#include <string>
#include "common/config/abstract_configuration.h"

class Application
{
public:
	
	Application(){}
	
	~Application();
	
	int main(int argc, char** argv);
	
	void deinit_all();
	
	void stream_converter(AbstractConfiguration*, std::string, std::string, std::string, Uint32, Uint32);


};

#endif /*APPLICATION_H_*/
