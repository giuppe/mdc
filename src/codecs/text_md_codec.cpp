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
#include "hashtable.h"

void TextMDCodec::set_descriptor_number (Uint8& descriptors) {
	descriptor_number = descriptors;
}

Uint8 TextMDCodec::get_descriptor_number () {
	return descriptor_number;
}

void TextMDCodec::code(const AbstractStream* stream, MDStream* md_stream) 
{
	for (Uint8 i=0; i<descriptor_number; i++) {
		Descriptor* descriptor= new Descriptor;
		descriptor->set_file_name(stream->get_stream_name()+".mdc");
		descriptor->set_flow_id(i);
		descriptor->set_codec_name("text");
		descriptor->set_payload_size(1024);
		descriptor->set_hash();//insert an hash sha1 / sha2, code based on contents
		Uint32 dim = (dynamic_cast<const TextStream*>(stream))->get_characters_dim();
		for (Uint32 i=0; i <= dim; i++) {
			(dynamic_cast<const TextStream*>(stream))->get_character(i);
			descriptor->set_sequence_number();//insert Uint32
			descriptor->set_payload();//must be created?
			md_stream->set_descriptor(descriptor);
		}
	}
}
