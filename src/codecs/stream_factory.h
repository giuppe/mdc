/***************************************************************************
                          data_chunk.cpp  -  DataChunk class
                             -------------------
    begin                : Nov 12 2007
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

#include "defs.h"
#include "abstract_stream.h"


#ifndef STREAM_FACTORY_H_
#define STREAM_FACTORY_H_

class StreamFactory
{
public:
	static AbstractStream* create_stream(string codec_name);
};

#endif /*STREAM_FACTORY_H_*/
