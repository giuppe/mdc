/***************************************************************************
                          log_manager.cpp  -  Log Manager class
                             -------------------
    begin                : Jul 13 2007
    copyright            : (C) 2007 by Giuseppe D'Aqui'
    email                : kumber@tiscalinet.it
 ***************************************************************************/

/***************************************************************************
 *                                                                                                                 
 *   This program is free software; you can redistribute it and/or modify  
 *   it under the terms of the GNU General Public License, Version 2,        
 *   as published by the Free Software Foundation.                                  
 *                                                                                                                 
 ***************************************************************************/



#include <ctime>
#include "log_manager.h"



void LogManager::init(bool console_output, const string& log_file)
{
	m_console_output = console_output;
	
	m_log_file.open(log_file.c_str(), fstream::out | fstream::app);
	
	if(m_log_file.fail())
	{
		cout<<"Error opening "<<log_file<<" for logging."<<endl;
	}
	else
	{

		time_t current_time;
		time(&current_time);
		string log_started ("\n\n****\nLog started - ");
		string current_time_string (asctime(localtime ( &current_time )));
		string end_header("****\n\n");
		
		m_log_file.write(log_started.c_str(), log_started.size());
		m_log_file.write(current_time_string.c_str(), current_time_string.size());
		m_log_file.write(end_header.c_str(), end_header.size());
		
		cout<<"\n****\nLog started - "<<asctime(localtime ( &current_time ))<<"****\n"<<endl;
	}
	
}



void LogManager::deinit()
{
	//m_log_file.flush();
	m_log_file.close();
}



void LogManager::debug(const char* log_string)
{
	string log_string2(log_string);
	m_log_file.write(log_string2.c_str(), log_string2.size());
	
	if(m_console_output==true)
	{
		cout<<log_string;
	}
	m_log_file.flush();
}

LogManager& LogManager::operator<<(const string& log_string)
{
	this->debug(log_string.c_str());
	return *this;
}

LogManager& LogManager::operator<<(const char* log_string)
{
	this->debug(log_string);
	return *this;
}

LogManager& LogManager::operator<<(Uint32 log_string)
{
	char* temp = new char[255];
	sprintf(temp, "%d", log_string);
	this->debug(temp);
	delete [] temp;
	return *this;
}

LogManager& LogManager::operator<<(Sint32 log_string)
{
	char* temp = new char[255];
	sprintf(temp, "%d", log_string);
	this->debug(temp);
	delete []temp;
	return *this;
}

LogManager& LogManager::operator<<(Uint16 log_string)
{
	char* temp = new char[255];
	sprintf(temp, "%d", log_string);
	this->debug(temp);
	delete []temp;
	return *this;
}

LogManager& LogManager::operator<<(Sint16 log_string)
{
	char* temp = new char[255];
	sprintf(temp, "%d", log_string);
	this->debug(temp);
	delete []temp;
	return *this;
}

LogManager& LogManager::operator<<(Uint8 log_string)
{
	char* temp = new char[255];
	sprintf(temp, "%d", log_string);
	this->debug(temp);
	delete []temp;
	return *this;
}

LogManager& LogManager::operator<<(Sint8 log_string)
{
	char* temp = new char[255];
	sprintf(temp, "%d", log_string);
	this->debug(temp);
	delete []temp;
	return *this;
}






LogManager* LogManager::_instance = 0;

LogManager* LogManager::instance()
{
	if(_instance==0)
	{
		_instance=new LogManager();
	}
	return _instance;
}


