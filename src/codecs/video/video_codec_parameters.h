/***************************************************************************
           video_codec_parameters.h  -  Video Codec Parameters class
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

#include "defs.h"
#include "../../common/data/i_data_chunk.h"
#include "../../common/serializable.h"
#include "../abstract_codec_parameters.h"

#ifndef VIDEO_CODEC_PARAMETERS_H_
#define VIDEO_CODEC_PARAMETERS_H_

class VideoCodecParameters : public AbstractCodecParameters {
private:
	Uint16 m_width;
	Uint16 m_height;
	Uint8 m_bits_per_pixel;
	Uint32 m_frame_number;
public:
	
	/*
	 * Sets video frame number parameter.
	 * @number: video frame number
	 */
	void set_frame_number(Uint32 number);
	
	/*
	 * Gets video frame number parameter.
	 * @returns: video frame number
	 */
	Uint32 get_frame_number();
	
	/*
	 * Gets image width size in pixel.
	 * @returns: image width size
	 */
	Uint16 get_width();
	
	/*
	 * Sets image width size parameter.
	 * @width: image width
	 */
	void set_width(Uint16 width);
	
	/*
	 * Gets image height size in pixel.
	 * @returns: image height size
	 */
	Uint16 get_height();
	
	/*
	 * Sets image height size parameter.
	 * @height: image height
	 */
	void set_height(Uint16 height);

	/*
	 * Gets coded bits number of each pixel.
	 * @returns: bits number
	 */
	Uint8 get_bits_per_pixel();
	
	/*
	 * Sets coding bits number of each pixel.
	 * @bits_number: bits number
	 */
	void set_bits_per_pixel(Uint8 bits_number);
	
	/*
	 * Initialize image codec parameters.
	 */
	VideoCodecParameters();

	/*
	 * Serialize a data chunk.
	 * @returns: data chunk
	 */
	MemDataChunk& serialize() const;

	/*
	 * Deserialize a data chunk.
	 */
	bool deserialize(const IDataChunk* dc);
	
	/*
	 * Get parameters' size.
	 * @returns: parameters' size
	 */
	Uint32 get_size() const;
	
	~VideoCodecParameters();
};

#endif /*VIDEO_CODEC_PARAMETERS_H_*/
