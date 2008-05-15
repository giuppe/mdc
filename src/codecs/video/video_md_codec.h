/***************************************************************************
                    video_md_codec.h  -  MD codec class for videos
                             -------------------
    begin                : May 7, 2008
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

#include "video_stream.h"
#include "../mdc/md_stream.h"
#include "../abstract_stream.h"
#include "../abstract_md_codec.h"

#ifndef VIDEO_MD_CODEC_H_
#define VIDEO_MD_CODEC_H_

#define VIDEO_CODEC_TYPE_CODE 3
#define VIDEO_CODEC_TYPE_STRING "video"

class VideoMDCodec : public AbstractMDCodec{
private:
	vector<Uint8> m_flows_id;
	vector<Uint32> m_seq_counter;
	pixel_container m_null_pixel;
public:
	/*
	 * Initialize parameter of a text mdcodec.
	 */
	VideoMDCodec();
	
	/*
	 * Code a single frame of a stream that to be sent.
	 * @stream: abstract stream to be coded
	 * @md_stream: flow group
	 */
	void code_frame(AbstractStream* stream, MDStream* md_stream) const;
	
	/*
	 * Decode the received stream.
	 * @md_stream: flow group
	 * @stream: abstract stream to be decoded
	 */
	void decode(const MDStream* md_stream, AbstractStream* stream) const;
	
	~VideoMDCodec();

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
	
	std::string get_codec_type_string(){return std::string(VIDEO_CODEC_TYPE_STRING);}
	Uint8 get_codec_type_code(){return VIDEO_CODEC_TYPE_CODE;}
};

#endif /*VIDEO_MD_CODEC_H_*/
