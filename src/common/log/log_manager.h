/***************************************************************************
                          log_manager.h  -  Log Manager class
                             -------------------
    begin                : Jul 13 2007
    copyright            : (C) 2007 by Giuseppe D'Aqui'
    email                : kumber@tiscalinet.it
 ***************************************************************************/

/***************************************************************************
 *                                                                                                                 *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License, Version 2,        *
 *   as published by the Free Software Foundation.                                  *
 *                                                                                                                 *
 ***************************************************************************/

/**
 * \file log_manager.h
 * Contains MACROs for Log Subsystem.
 */

/**
 * \def LOG_INFO(x)
 * Outputs the string "x" to log file and/or console, together with function calling name.
 * Use it to log detailed debug information that should be removed from production code, 
 * as it works only if LOG_LEVEL >= 3.
 * \param x the string to log, or multiple strings concatenated by operator "<<"
 */

/**
 * \def LOG_WARN(x)
 * Outputs the string "x" to log file and/or console, together with function calling name.
 * Use it to log detailed debug warnings that might be removed from production code,
 * as it works only if LOG_LEVEL >= 2.
 * \param x the string to log, or multiple strings concatenated by operator "<<"
 */

/**
 * \def LOG_ERROR(x)
 * Outputs the string "x" to log file and/or console, together with function calling name.
 * Use it to log detailed error description, for non-fatal errors.
 * Works only if LOG_LEVEL >= 1.
 * \param x the string to log, or multiple strings concatenated by operator "<<"
 */

/**
 * \def LOG_FATAL(x)
 * Outputs the string "x" to log file and/or console, together with function calling name.
 * Use it to log detailed error description, for fatal errors (e.g. unrecoverable errors).
 * Works on every LOG_LEVEL.
 * \param x the string to log, or multiple strings concatenated by operator "<<"
 */

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <SDL/SDL.h>

#ifndef LOG_MANAGER_H_
#define LOG_MANAGER_H_

#ifndef LOG_LEVEL
#define LOG_LEVEL 3
#endif

#ifdef DEBUG
#define DEBUG_OUT(x) {*LogManager::instance()<<x;}
#else
#define DEBUG_OUT(x)
#endif


#if LOG_LEVEL  == 3
#define LOG_INFO(x) {*LogManager::instance()<<"INFO : ["<<typeid(this).name()<<"::"<<__func__<<"] "<<x<<"\n";}
#define LOG_WARN(x) {*LogManager::instance()<<"WARN : ["<<typeid(this).name()<<"::"<<__func__<<"]" <<x<<"\n";}
#define LOG_ERROR(x) {*LogManager::instance()<<"ERROR: ["<<typeid(this).name()<<"::"<<__func__<<"]" <<x<<"\n";}
#define LOG_FATAL(x) {*LogManager::instance()<<"FATAL: ["<<typeid(this).name()<<"::"<<__func__<<"]" <<x<<"\n";}
#define LOG_INFO_STATIC(x) {*LogManager::instance()<<"INFO : ["<<__func__<<"]" <<x<<"\n";}
#define LOG_WARN_STATIC(x) {*LogManager::instance()<<"WARN : ["<<__func__<<"]" <<x<<"\n";}
#define LOG_ERROR_STATIC(x) {*LogManager::instance()<<"ERROR: ["<<__func__<<"]" <<x<<"\n";}
#define LOG_FATAL_STATIC(x) {*LogManager::instance()<<"FATAL: ["<<__func__<<"]" <<x<<"\n";}
#else 
#if LOG_LEVEL == 2
#define LOG_INFO(x) 
#define LOG_WARN(x) {*LogManager::instance()<<"WARN : ["<<typeid(this).name()<<"::"<<__func__<<"]" <<x<<"\n";}
#define LOG_ERROR(x) {*LogManager::instance()<<"ERROR: ["<<typeid(this).name()<<"::"<<__func__<<"]" <<x<<"\n";}
#define LOG_FATAL(x) {*LogManager::instance()<<"FATAL: ["<<typeid(this).name()<<"::"<<__func__<<"]" <<x<<"\n";}
#define LOG_INFO_STATIC(x)
#define LOG_WARN_STATIC(x) {*LogManager::instance()<<"WARN : ["<<__func__<<"]" <<x<<"\n";}
#define LOG_ERROR_STATIC(x) {*LogManager::instance()<<"ERROR: ["<<__func__<<"]" <<x<<"\n";}
#define LOG_FATAL_STATIC(x) {*LogManager::instance()<<"FATAL: ["<<__func__<<"]" <<x<<"\n";}
#else 
#if LOG_LEVEL == 1
#define LOG_INFO(x) 
#define LOG_WARN(x) 
#define LOG_ERROR(x) {*LogManager::instance()<<"ERROR: ["<<typeid(this).name()<<"::"<<__func__<<"]" <<x<<"\n";}
#define LOG_FATAL(x) {*LogManager::instance()<<"FATAL: ["<<typeid(this).name()<<"::"<<__func__<<"]" <<x<<"\n";}
#define LOG_INFO_STATIC(x)
#define LOG_WARN_STATIC(x)
#define LOG_ERROR_STATIC(x) {*LogManager::instance()<<"ERROR: ["<<__func__<<"]" <<x<<"\n";}
#define LOG_FATAL_STATIC(x) {*LogManager::instance()<<"FATAL: ["<<__func__<<"]" <<x<<"\n";}
#else 
#if LOG_LEVEL == 0
#define LOG_INFO(x) 
#define LOG_WARN(x) 
#define LOG_ERROR(x) 
#define LOG_FATAL(x) {*LogManager::instance()<<"FATAL: ["<<typeid(this).name()<<"::"<<__func__<<"]" <<x<<"\n";}
#define LOG_INFO_STATIC(x)
#define LOG_WARN_STATIC(x)
#define LOG_ERROR_STATIC(x)
#define LOG_FATAL_STATIC(x) {*LogManager::instance()<<"FATAL: ["<<__func__<<"]" <<x<<"\n";}
#endif
#endif
#endif
#endif

/**
 * Singleton used for managing log files.
 * Should be initialized as the application starts.
 * For logging a string you should not use directly the LogManager meber functions; instead, use 
 * the macro wrappers LOG_INFO, LOG_WARN, LOG_ERROR and LOG_FATAL.
 * @sa LOG_INFO, LOG_WARN, LOG_ERROR, LOG_FATAL
 */
class LogManager
{
private:
	bool m_console_output;
	
	std::fstream m_log_file;
	
public:
	
	/**
	 * Initializes the Log Manager.
	 * @param console_output if true, shows logged strings in console.
	 * @param log_file the path to the log file.
	 */
	void init(bool console_output, const std::string& log_file);
	
	void deinit();

	void debug(const char* log_string);
	
	LogManager& operator<<(const std::string& log_string);
	
	LogManager& operator<<(const char* log_string);
	
	LogManager& operator<<(Uint32 log_string);
	
	LogManager& operator<<(Sint32 log_string);
	
	LogManager& operator<<(Uint16 log_string);
	
	LogManager& operator<<(Sint16 log_string);

	LogManager& operator<<(Uint8 log_string);
	
	LogManager& operator<<(Sint8 log_string);
	
//	std::fstream& get_log_file();

	// begin Singleton stuff

private:

	static LogManager* _instance;

protected:

	LogManager():m_console_output(true){};
	~LogManager(){deinit();}

public:

	/**
	 * Permits access to the sole Singleton instance.
	 * @returns the LogManager instance.
	 */
	static LogManager* instance();

	// end Singleton stuff

};

#endif /*LOG_MANAGER_H_*/
