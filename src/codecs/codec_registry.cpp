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
#include "pcx/pcx_md_codec.h"
#include "mpeg/mpeg_md_codec.h"


void CodecRegistry::register_codec(const string& name, AbstractMDCodec* codec)
{
	LOG_INFO("Registering codec: "<<name);
	m_codecs[name]= codec;
}


bool CodecRegistry::get_codec(const string& name, AbstractMDCodec*& codec) const
{
	
	map<string, AbstractMDCodec*>::const_iterator it;
		
	it = m_codecs.find(name);
		
	if(it==m_codecs.end())
	{
		LOG_ERROR("No codec named "<<name<<" found.");
		return false;
	}

	
	
	codec= it->second;
	
	return true;
}

void CodecRegistry::init() {
	this->register_codec(string("text"), new TextMDCodec());
	register_codec(string("mpeg"), new MpegMDCodec());
	register_codec(string("image"), new ImageMDCodec());
#ifdef MDC_PCX_IS_WORKING
	this->register_codec(string("pcx"), new PcxMDCodec());
#endif
}

void CodecRegistry::deinit()
{
	map<string, AbstractMDCodec*>::const_iterator it;
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


