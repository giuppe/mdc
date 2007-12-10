/***************************************************************************
                          xml_configuration.h  -  Insert description
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

#include "abstract_configuration.h"

#include "../defs.h"

#ifndef XML_CONFIGURATION_H_
#define XML_CONFIGURATION_H_



class TiXmlDocument;

/**
 * Represents configuration through an XML file.
 */
class XMLConfiguration : public AbstractConfiguration
{
	private:
	
		TiXmlDocument* m_document;
		
		bool get_value(const string& section, const string& object, string& value) const;
		
	//	string get_section(const string& object_path) const;
		
	//	string get_object_name(const string& object_path) const;
		
		void set_value(const string& section, const string& object, const string& value);
		
		bool m_initialized;
		
		string m_file_path;
		

	public:
	
		/**
		 * Constructor for XMLConfiguration.
		 * @param file_path the path to xml file used for configuration.
		 * @param create_if_missing if it is true and the specified file is non-existent, constructor creates the file.
		 */ 
		XMLConfiguration(const string& file_path, bool create_if_missing = false);
		
		~XMLConfiguration();
		
		bool get_string(const string& section_name, const string& object_name, string& value) const;
		
		bool get_int(const string& section_name, const string& object_name, Uint32& value) const;
	
		bool get_bool(const string& section_name, const string& object_name, bool& value) const;
	
	//	bool get_double(const string& object_name, double& value) const;
	
		void save();
		
		void remove_object(const string& section_name, const string& object_name);
		
		void remove_section(const string& section_name);
	
		void set_string(const string& section_name, const string& object_name, const string& value);
	
		void set_int(const string& section_name, const string& object_name, const Uint32& value);
	
		void set_bool(const string& section_name, const string& object_name, const bool& value);
	
	//	void set_double(const string& object_name, const double& value);
		
};

#endif /*XML_CONFIGURATION_H_*/
