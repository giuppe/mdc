/***************************************************************************
                    image_md_codec.h  -  MD codec class for images
                             -------------------
    begin                : Dec 13, 2007
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

#include "image_stream.h"
#include "../mdc/md_stream.h"
#include "../abstract_stream.h"
#include "../abstract_md_codec.h"

#ifndef IMAGE_MD_CODEC_H_
#define IMAGE_MD_CODEC_H_

#define IMAGE_CODEC_TYPE_CODE 2
#define IMAGE_CODEC_TYPE_STRING "image"

class ImageMDCodec : public AbstractMDCodec {
private:
	vector<Uint32> m_seq_counter;
	pixel_container m_null_pixel;
	
	/*
	 * Execute decompression of a compressed payload.
	 * @compressed_payload: compressed payload
	 * @payload_size: compressed payload dimension
	 * @returns: a pointer to the decompressed data contained in compressed payload
	 */
	MemDataChunk* decompression(MemDataChunk* compressed_payload, Uint16 payload_size) const;
	
public:
	/*
	 * Initialize parameter of an image mdcodec.
	 */
	ImageMDCodec();
	
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
	~ImageMDCodec();

	/*
	 * Sets the flows number.
	 * @number: flows number into which the generic stream must to be divided
	 * before coding process
	 */
	void set_flows_number (Uint8 number);

	/*
	 * Sets the payload size of descriptor.
	 * @size: desidered size of each descriptor
	 */
	void set_preferred_payload_size (Uint16 size);
	
	/*
	 * Sets null pixel color components.
	 * @size: desidered size of each descriptor
	 */
	void set_null_pixel_colors(Uint8 r, Uint8 g, Uint8 b);
	
	/*
	 * Gets null pixel color components.
	 * @returns: pixel color components
	 */
	pixel_container get_null_pixel_colors();
	
	std::string get_codec_type_string(){return std::string(IMAGE_CODEC_TYPE_STRING);}
		
	Uint8 get_codec_type_code(){return IMAGE_CODEC_TYPE_CODE;}
};

#endif /*IMAGE_MD_CODEC_H_*/
