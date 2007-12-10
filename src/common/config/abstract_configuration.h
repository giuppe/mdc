/***************************************************************************
                          abstract_configuration.h  -  Insert description
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

#include <string>
#include <SDL/SDL.h>

#ifndef ABSTRACT_CONFIGURATION_H_
#define ABSTRACT_CONFIGURATION_H_

/**
 * Represents an abstract configuration object, a sort of database containing pairs of
 * configuration options and their values.
 * @sa CommandlineConfiguration, XMLConfiguration
 */
class AbstractConfiguration
{
protected:
	virtual bool get_string(const string& section_name, const string& object_name, string& value) const =0;
	
	virtual bool get_int(const string& section_name, const string& object_name, Uint32& value) const =0;
	
	virtual bool get_bool(const string& section_name, const string& object_name, bool& value) const =0;
	
//	virtual bool get_double(const string& object_name, double& value) const =0;
	
	virtual void remove_object(const string& section_name, const string& object_name) = 0;
	
	virtual void remove_section(const string& section_name) = 0;
	
	virtual void set_string(const string& section_name, const string& object_name, const string& value) =0;
	
	virtual void set_int(const string& section_name, const string& object_name, const Uint32& value) =0;
	
	virtual void set_bool(const string& section_name, const string& object_name, const bool& value) =0;
	
//	virtual void set_double(const string& object_name, const double& value) =0;

	
public:
	
	
	virtual void save()=0;
	
	
	virtual ~AbstractConfiguration(){};
			
};

#endif /*ABSTRACT_CONFIGURATION_H_*/
