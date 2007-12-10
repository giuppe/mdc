/***************************************************************************
                          commandline_configuration.h  -  Insert description
                             -------------------
    begin                : Jun 13, 2007
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

#include "../defs.h"
#include "abstract_configuration.h"



#ifndef COMMANDLINE_CONFIGURATION_H_
#define COMMANDLINE_CONFIGURATION_H_


/**
 * Represents configuration through command line arguments.
 */
class CommandlineConfiguration : public AbstractConfiguration
{
	protected:
		map< string, string> m_arguments;
		
		void parse_arguments(const vector<string>& arguments);
	
		bool get_string(const string& section_name, const string& object_name, string& value) const;
		
		bool get_int(const string& section_name, const string& object_name, Uint32& value) const;
	
		bool get_bool(const string& section_name, const string& object_name, bool& value) const;

		void remove_object(const string& section_name, const string& object_name){};
		
		void remove_section(const string& section_name){};
	
		void set_string(const string& section_name, const string& object_name, const string& value){};
	
		void set_int(const string& section_name, const string& object_name, const Uint32& value){};
	
		void set_bool(const string& section_name, const string& object_name, const bool& value){};

		
	public:
		/**
		 * Constructor for CommandlineConfiguration.
		 */ 
		CommandlineConfiguration(){};
		
		/**
			 * Initializer for CommandlineConfiguration.
			 * @param argc thenumber of command line arguments.
			 * @param argv arguments as array of c-strings
			 */ 
		void init(Sint32 argc, char* argv[]);
		
	
	//	bool get_double(const string& object_name, double& value) const;
		/**
		 * This function does nothing, as command line arguments are read-only.
		 */
		void save(){};
		
	
	//	void set_double(const string& object_name, const double& value){};
		
};

#endif /*COMMANDLINE_CONFIGURATION_H_*/
