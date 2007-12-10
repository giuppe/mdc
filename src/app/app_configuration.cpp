/***************************************************************************
              app_configuration.cpp  -  Configuration Manager class
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
#include "app_configuration.h"
#include "../common/config/xml_configuration.h"
#include <string>

void AppConfiguration::init() {
	m_xml_config = new XMLConfiguration("./config.xml", true);
	Uint32 control_port;
	if (m_xml_config->get_int(string("network"), string("control_port"), control_port))
		m_control_port = control_port;
	else {
		m_control_port = 5551;
		m_xml_config->set_int(string("network"), string("control_port"), m_control_port);
	}
	Uint32 data_port;
	if (m_xml_config->get_int(string("network"), string("data_port"), data_port))
		m_data_port = data_port;
	else {
		m_data_port = 5552;
		m_xml_config->set_int(string("network"), string("data_port"), m_data_port);
	}
	string path;
	if (m_xml_config->get_string(string("repository"), string("path"), path))
		m_repository_path = path;
	else {
		m_repository_path = "./shared";
		m_xml_config->set_string(string("repository"), string("path"), m_repository_path);
	}
}

void AppConfiguration::deinit() {
	m_xml_config->save();
	delete m_xml_config;
}

AppConfiguration* AppConfiguration::_instance = 0;

AppConfiguration* AppConfiguration::instance() {
	if (_instance == 0)
		_instance = new AppConfiguration();
	return _instance;
}

Uint16 AppConfiguration::get_control_port() {return m_control_port;}
Uint16 AppConfiguration::get_data_port() {return m_data_port;}
string AppConfiguration::get_repository_path() {return m_repository_path;}
