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
#include "text/text_stream.h"
#include "pcx/pcx_stream.h"
#include <string>
#include "stream_factory.h"
#include "mpeg/mpeg_stream.h"

AbstractStream* StreamFactory::create_stream(string codec_name)
{
	LOG_INFO_STATIC("Creating stream of type: "<<codec_name);
	if(codec_name=="text")
	{
		return new TextStream();
	}
	if (codec_name == "mpeg") return new MpegStream();
#ifdef MDC_PCX_IS_WORKING
	else if(codec_name=="pcx")
	{
		return new PcxStream();
	}
#endif
	LOG_FATAL_STATIC("Unable to manage stream of type: "<<codec_name);
	exit(1);
}

