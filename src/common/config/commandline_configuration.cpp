/***************************************************************************
                          commandline_configuration.cpp  -  Insert description
                             -------------------
    begin                : Jun 30, 2007
    copyright          : (C) 2007 by Giuseppe D'Aqui'
    email                : giuseppe.da@gmail.com
 ***************************************************************************/

/***************************************************************************
 *                                                                                                                 
 *   This program is free software; you can redistribute it and/or modify  
 *   it under the terms of the GNU General Public License, Version 2,        
 *   as published by the Free Software Foundation.                                  
 *                                                                                                                 
 ***************************************************************************/

#include "commandline_configuration.h"
#include <map>
#include <string>
#include <cassert>
#include <cstring>
#include <vector>


void CommandlineConfiguration::init(Sint32 argc, char* argv[])
{
	vector<string> arguments;
	
	for(Sint32 i = 1; i<argc; i++)
	{
		arguments.push_back(string(argv[i]));
	}
	
	parse_arguments(arguments);
	
}

void CommandlineConfiguration::parse_arguments(const vector<string>& arguments)
{
	
	Uint32 it = 0;

	
	string curr_arg("");
	
	string prev_arg("");
	
	while (  it < arguments.size())
	{
    	curr_arg = arguments[it];
		if(curr_arg.substr(0, 2) == "--")
		{
			//DEBWARN("Argument: "<<curr_arg.substr(2)<<"\n");
			if(prev_arg.substr(0, 2) == "--")
			{
				string object_name(prev_arg.substr(2)); 
				m_arguments[object_name] = string("true");
				LOG_INFO("Setting "<<object_name<<" = true\n");
			}
			
			if(it == arguments.size()-1)
			{
				string object_name(curr_arg.substr(2)); 
				m_arguments[object_name] = string("true");
				LOG_INFO("Setting "<<object_name<<" = true\n");
			}
			prev_arg = curr_arg;
		}
		else
		{
			if(prev_arg.substr(0, 2) == "--")
			{
				string object_name(prev_arg.substr(2)); 
				m_arguments[object_name] = curr_arg;
				LOG_INFO("Setting "<<object_name<<" = "<<curr_arg<<"\n");
				
			}
			else if(curr_arg.substr(0, 2) == "--")
			{
				LOG_ERROR("Invalid option: "<<curr_arg<<"\n");
				
			}
			prev_arg = curr_arg;
			//assert(0);
		}
		it++;	    		
	}
	
	
}

bool CommandlineConfiguration::get_string(const string& section_name, const string& object_name, string& value) const
{
	if(m_arguments.count(object_name)==0)
		return false;

	map<string, string>::const_iterator it;
	
	it = m_arguments.find(object_name);
	
	value = it->second;
	return true;
	
}
		
bool CommandlineConfiguration::get_int(const string& section_name, const string& object_name, Uint32& value) const
{
	if(m_arguments.count(object_name)==0)
		return false;

	map<string, string>::const_iterator it;
	
	it = m_arguments.find(object_name);
	
	value = atoi(it->second.c_str());
	return true;
	
}
	
bool CommandlineConfiguration::get_bool(const string& section_name, const string& object_name, bool& value) const
{

	if(m_arguments.find(object_name)==m_arguments.end())
	{
		value=false;
	
		return false;
	}
	
	map<string, string>::const_iterator it;
	
	it = m_arguments.find(object_name);
	
	
	if(it->second=="true")
	{
		value = true;
	}
	else
	{
		value = false;
	}
	
	return true;
	
}



