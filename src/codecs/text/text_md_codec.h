/***************************************************************************
                    text_md_codec.h  -  MD codec class for text
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
#include "../mdc/md_stream.h"
#include "../abstract_stream.h"
#include "../abstract_md_codec.h"
#include <vector>

#ifndef TEXT_MD_CODEC_H_
#define TEXT_MD_CODEC_H_

class TextMDCodec : public AbstractMDCodec{
private:
	vector<Uint8> m_flows_id;
	vector<Uint32> m_seq_counter;

public:
	/*
	 * Initialize parameter of a text mdcodec.
	 */
	TextMDCodec();
	
	
	/*
	 * Code the stream to be sent.
	 * @stream: abstract stream to be coded
	 * @md_stream: flow group
	 */
	void code(AbstractStream* stream, MDStream* md_stream) const;
	
	/*
	 * Decode the received stream.
	 * @md_stream: flow group
	 * @stream: abstract stream to be decoded
	 */
	void decode(const MDStream* md_stream, AbstractStream* stream) const;
	~TextMDCodec();

	/*
	 * Sets the flows number.
	 * @number: flows number into which the generic stream must to be divided before coding
	 * process
	 */
	void set_flows_number (Uint8 number);

	/*
	 * Sets the payload size of descriptor.
	 * @size: desidered size of each descriptor
	 */
	void set_preferred_payload_size (Uint16 size);
};

#endif /*TEXT_MD_CODEC_H_*/
