/***************************************************************************
                          xml_configuration.cpp  -  Insert description
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

#include "xml_configuration.h"

#include <cstring>
#include <cassert>
#include "tinyxml/tinyxml.h"




bool XMLConfiguration::get_value(const string& section, const string& object, string& value) const
{
	if(m_initialized == true)
	{
		TiXmlHandle docHandle( m_document );
		
		TiXmlText* object_value = docHandle.FirstChild(section.c_str()).FirstChild(object.c_str()).FirstChild().Text();
		if(object_value)
		{
		
			value = object_value->Value(); 
			
			LOG_INFO("XMLConfiguration: "<<section<<"/"<<object<<" is "<<value);
			
			return true;
		}	
	
		LOG_WARN("XMLConfiguration: cannot load "<<section<<"/"<<object);
		return false;
	
	}
	LOG_FATAL("XMLConfiguration: not initialized.");
	assert(0);
	return false;
	
	
}




XMLConfiguration::XMLConfiguration(const string& file_path, bool create_if_missing)
{
	m_document = new TiXmlDocument();
	
	m_initialized = false;
	
	if(m_document->LoadFile(file_path.c_str()))
	{	
		m_initialized = true;

		m_file_path = file_path;
	
	}
	else if(create_if_missing == true)
	{
	
		m_file_path = file_path;
		
		m_initialized= true;
	}	
}



XMLConfiguration::~XMLConfiguration()
{
	if(m_initialized==true)
		delete m_document;	
}
		



bool XMLConfiguration::get_string(const string& section_name, const string& object_name, string& value) const
{
	
	return get_value(section_name, object_name, value);
}



bool XMLConfiguration::get_int(const string& section_name, const string& object_name, Uint32& value) const
{
	string value_string;
	bool result = get_value(section_name, object_name, value_string);
	if(result==true)
	{
		value = atoi(value_string.c_str());
	}
	return result;
}


	
bool XMLConfiguration::get_bool(const string& section_name, const string& object_name, bool& value) const
{
	string value_string;
	bool result = get_value(section_name, object_name, value_string);
	
	if(result == true)
	{
		if(value_string == "true")
		{
			value = true;
		}
		else
		{
			value = false;
		}
	}
	
	return result;
}

	


void XMLConfiguration::save()
{
	m_document->SaveFile(m_file_path.c_str());
}



	
void XMLConfiguration::set_string(const string& section_name, const string& object_name, const string& value)
{
	this->set_value(section_name, object_name, value);
}




void XMLConfiguration::set_int(const string& section_name, const string& object_name, const Uint32& value)
{
	char string_value[255];
	sprintf(string_value, "%d", value);
	this->set_value(section_name, object_name, string(string_value));
}


	
	
void XMLConfiguration::set_bool(const string& section_name, const string& object_name, const bool& value)
{
	string string_value = "false";
	if(value == true)
	{
		string_value = "true";
	}
	this->set_value(section_name, object_name, string_value);
}
	

void XMLConfiguration::set_value(const string& section, const string& object, const string& value)
{
	bool section_found = false;
	bool object_found = false;
	
	TiXmlNode* child = 0;
	
	TiXmlNode* nephew = 0;
	
	if(m_document->NoChildren()==false)
	{
		
		while((!section_found) && ( child = m_document->IterateChildren( child ) ))
		{
			if(string(child->Value())==section)
			{
				section_found = true;
			}
		}
	}
		
	if(section_found == false)
	{
		LOG_INFO("XMLConfiguration: no section "<<section<<" found, creating.");
		child = new TiXmlElement( section.c_str() );
		m_document->LinkEndChild( child );
	}
	
	if(child->NoChildren()==false)
	{
		
		while((!object_found) &&( nephew = child->IterateChildren( nephew ) ))
		{
			if(string(nephew->Value())==object)
			{
				object_found = true;
			}
		}
	}
	
	if(object_found == false)
	{
		LOG_INFO("XMLConfiguration: no object "<<section<<"/"<<object<<" found, creating.");
		nephew = new TiXmlElement( object.c_str() );
		child->LinkEndChild( nephew );
	}
	
	nephew->Clear();
	
	TiXmlText* text_element = new TiXmlText( value.c_str() );
	nephew->LinkEndChild( text_element );
	
}


void XMLConfiguration::remove_object(const string& section_name, const string& object_name)
{
	bool section_found = false;
	bool object_found = false;
	
	TiXmlNode* child = 0;
	
	TiXmlNode* nephew = 0;
	
	if(m_document->NoChildren()==false)
	{
		
		while((!section_found) && ( child = m_document->IterateChildren( child ) ))
		{
			if(string(child->Value())==section_name)
			{
				section_found = true;
			}
		}
	}
		
	if(section_found == false)
	{
		return;
	}
	
	if(child->NoChildren()==false)
	{
		
		while((!object_found) && ( nephew = child->IterateChildren( nephew ) ))
		{
			if(string(nephew->Value())==object_name)
			{
				object_found = true;
			}
		}
	}
	
	if(object_found == false)
	{
		return;
	}
	
	child->RemoveChild(nephew);
}

void XMLConfiguration::remove_section(const string& section_name)
{
	bool section_found = false;

	
	TiXmlNode* child = 0;
		
	if(m_document->NoChildren()==false)
	{
		
		while((!section_found) && ( child = m_document->IterateChildren( child ) ))
		{
			if(string(child->Value())==section_name)
			{
				section_found = true;
			}
		}
	}
		
	if(section_found == false)
	{
		return;
	}
	
	m_document->RemoveChild(child);
}
