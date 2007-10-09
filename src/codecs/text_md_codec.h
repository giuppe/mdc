/***************************************************************************
                          TextMDCodec.h  -  MD codec for text class
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
#include "text_stream.h"
#include "md_stream.h"
#include "abstract_stream.h"
#include "abstract_md_codec.h"

#ifndef TEXT_MD_CODEC_H_
#define TEXT_MD_CODEC_H_

class TextMDCodec : public AbstractMDCodec{
private:
	Uint8 descriptor_number;
public:
	void set_descriptor_number (Uint8& descriptors);
	Uint8 get_descriptor_number ();
	void code(const AbstractStream* stream, MDStream* md_stream);
	void decode(const MDStream* md_stream, AbstractStream* stream);
	~TextMDCodec(){};
};

#endif /*TEXT_MD_CODEC_H_*/
