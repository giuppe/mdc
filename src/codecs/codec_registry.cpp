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

#include "image/image_md_codec.h"
#include "abstract_md_codec.h"
#include "text/text_md_codec.h"



void CodecRegistry::register_codec(AbstractMDCodec* codec)
{
	string name = codec->get_codec_type_string();
	LOG_INFO("Registering codec: "<<name);
	m_codec_names[codec->get_codec_type_string()]= codec->get_codec_type_code();
	m_codecs[codec->get_codec_type_code()] = codec;
}


bool CodecRegistry::get_codec(const string& name, AbstractMDCodec*& codec) const
{

	map<string, Uint8>::const_iterator it;

	it = m_codec_names.find(name);

	if(it==m_codec_names.end())
	{
		LOG_ERROR("No codec named "<<name<<" found.");
		return false;
	}



	return get_codec(it->second, codec);


}

bool CodecRegistry::get_codec(Uint8 codec_code, AbstractMDCodec*& codec) const
{

	map<Uint8, AbstractMDCodec*>::const_iterator it_codec;

	it_codec = m_codecs.find(codec_code);

	if(it_codec==m_codecs.end())
	{
		LOG_ERROR("No codec of type "<<codec_code<<" found.");
		return false;
	}

	codec = it_codec->second;

	return true;
}


void CodecRegistry::init() {
	this->register_codec(new TextMDCodec());

	register_codec(new ImageMDCodec());
}

void CodecRegistry::deinit()
{
	map<Uint8, AbstractMDCodec*>::const_iterator it;
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


