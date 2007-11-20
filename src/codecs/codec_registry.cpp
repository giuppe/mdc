/***************************************************************************
                          codec_registry.cpp  -  Insert description
                             -------------------
    begin                : Jul 26, 2007
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

#include "defs.h"
#include "codec_registry.h"
#include <map>
#include <string>
#include "abstract_md_codec.h"
#include "text/text_md_codec.h"
#include "pcx/pcx_md_codec.h"


void CodecRegistry::register_codec(const std::string& name, AbstractMDCodec* codec)
{
	LOG_INFO("Registering codec: "<<name);
	m_codecs[name]= codec;
}


bool CodecRegistry::get_codec(const std::string& name, AbstractMDCodec*& codec) const
{
	if(m_codecs.count(name)==0)
	{
		LOG_ERROR("No codec named "<<name<<" found.");
		return false;
	}

	
	std::map<std::string, AbstractMDCodec*>::const_iterator it;
	
	it = m_codecs.find(name);
	
	codec= it->second;
	
	return true;
}

void CodecRegistry::init()
{

	this->register_codec(std::string("text"), new TextMDCodec());
	this->register_codec(std::string("pcx"), new PcxMDCodec());
		
}

void CodecRegistry::deinit()
{
	std::map<std::string, AbstractMDCodec*>::const_iterator it;
	for ( it=m_codecs.begin() ; it != m_codecs.end(); it++ )
	{
		delete it->second;
	}
	
}


CodecRegistry* CodecRegistry::_instance = 0;

CodecRegistry* CodecRegistry::instance()
{
	if(_instance==0)
	{
		_instance=new CodecRegistry();
	}
	return _instance;
}


