/***************************************************************************
                          codec_registry.h  -  Insert description
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


#include "abstract_md_codec.h"

#ifndef CODEC_REGISTRY_H_
#define CODEC_REGISTRY_H_



class CodecRegistry
{
private:
	map<string, AbstractMDCodec*> m_codecs;
	
	
public:
	
	void register_codec(const string& name, AbstractMDCodec* codec);
	
	bool get_codec(const string& name, AbstractMDCodec*& codec) const;

	void init();
	
	void deinit();
	// begin Singleton stuff

private:

static CodecRegistry* _instance;

protected:

CodecRegistry(){};
~CodecRegistry(){deinit();}

public:

static CodecRegistry* instance();

// end Singleton stuff
};

#endif /*CODEC_REGISTRY_H_*/
