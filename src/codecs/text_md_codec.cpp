/***************************************************************************
                          text_md_codec.cpp  -  Manage text codec
                             -------------------
    begin                : Oct 5, 2007
    copyright            : Livio Pipitone
    email                : livent@tiscalinet.it
 ***************************************************************************/

/***************************************************************************
 *                                                                                                                 
 *   This program is free software; you can redistribute it and/or modify  
 *   it under the terms of the GNU General Public License, Version 2,        
 *   as published by the Free Software Foundation.                                  
 *                                                                                                                 
 ***************************************************************************/

#include "text_md_codec.h"
#include "string.h"
#include "defs.h"
#include "text_stream.h"
#include "md_stream.h"
#include "descriptor.h"

void TextMDCodec::code(const AbstractStream* stream, MDStream* md_stream) 
{
	//FIXME this function doesn't do what it should...
	(dynamic_cast<const TextStream*>(stream))->get_character(0);
	Descriptor* descriptor= new Descriptor;
	descriptor->set_codec_name("text");
	descriptor->set_file_name("");
	md_stream->set_descriptor(descriptor);
}
