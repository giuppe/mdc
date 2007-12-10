/***************************************************************************
                 app_configuration.h  -  Configuration Manager class
                             -------------------
    begin                : Dec 5 2007
    copyright            : (C) 2007 by Livio Pipitone
    email                : livent@tiscalinet.it
 ***************************************************************************/

/***************************************************************************
 *                                                                                                                 
 *   This program is free software; you can redistribute it and/or modify  
 *   it under the terms of the GNU General Public License, Version 2,        
 *   as published by the Free Software Foundation.                                  
 *                                                                                                                 
 ***************************************************************************/

#include "defs.h"
#include <string>
#include "../common/config/xml_configuration.h"

#ifndef APP_CONFIGURATION_H_
#define APP_CONFIGURATION_H_
/**
 * Singleton used for configuring application actions.
 * Permits to save and load from an XML configuration file.
 */
class AppConfiguration {
private:
	Uint16 m_control_port;
	Uint16 m_data_port;
	string m_repository_path;
	XMLConfiguration* m_xml_config;
	
public:
	/**
	 * Initialize ports number and repository path.
	 */
	void init();
	
	void deinit();
	
	/*
	 * Gets control port number.
	 * @returns: control port number
	 */
	Uint16 get_control_port();
	
	/*
	 * Gets data port number.
	 * @returns: data port number
	 */
	Uint16 get_data_port();
	
	/*
	 * Gets repository path
	 * @returns: path of shared files folder 
	 */
	string get_repository_path();
	
// begin Singleton stuff
private:
    static AppConfiguration* _instance;

protected:
	AppConfiguration(){};
	~AppConfiguration() {deinit();}

public:
    static AppConfiguration* instance();
// end Singleton stuff
};

#endif /*APP_CONFIGURATION_H_*/
