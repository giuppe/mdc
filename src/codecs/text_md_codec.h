/***************************************************************************
                          TextMDCodec.h  -  MD codec class for text
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
	Uint8 m_flows_number;
public:
	
	/*
	 * Get flows number.
	 * @returns: flows number
	 */
	Uint8 get_flows_number ();
	
	/*
	 * Set flows number.
	 * @flows: flows number
	 * @dinal_position: read to this final position
	 */
	void set_flows_number (Uint8 flows);
	
	/*
	 * Code the stream.
	 * @stream: abstract stream to be coded
	 * @md_stream: flow group
	 */
	void code(const AbstractStream* stream, MDStream* md_stream);
	
	/*
	 * Decode the received stream.
	 * @md_stream: flow group
	 * @stream: abstract stream to be decoded
	 */
	void decode(const MDStream* md_stream, AbstractStream* stream);
	~TextMDCodec(){};
};

#endif /*TEXT_MD_CODEC_H_*/
