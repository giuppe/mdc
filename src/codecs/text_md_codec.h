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

#ifndef TEXT_MD_CODEC_H_
#define TEXT_MD_CODEC_H_

class TextMDCodec {
public:
	void code(const TextStream* stream, MDStream* md_stream);
	virtual void decode(const MDStream* md_stream, AbstractStream* stream) = 0;
	~TextMDCodec(){};
};

#endif /*TEXT_MD_CODEC_H_*/
