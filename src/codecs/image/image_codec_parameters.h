/***************************************************************************
           image_codec_parameters.h  -  Image Codec Parameters class
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

#include "defs.h"
#include "../../common/data/i_data_chunk.h"
#include "../../common/serializable.h"
#include "../abstract_codec_parameters.h"

#ifndef IMAGE_CODEC_PARAMETERS_H_
#define IMAGE_CODEC_PARAMETERS_H_

class ImageCodecParameters : public AbstractCodecParameters {
private:
	Uint16 m_width;
	Uint16 m_height;
	Uint8 m_bits_per_pixel;
public:
	
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
	ImageCodecParameters();

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
	
	
	~ImageCodecParameters();
};

#endif /*IMAGE_CODEC_PARAMETERS_H_*/
