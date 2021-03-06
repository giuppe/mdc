/***************************************************************************
                      image_stream.h  -  Image Stream class
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

#include <cstdlib>
#include <cstdio>
#include "../abstract_stream.h"
#include "../../common/data/mem_data_chunk.h"
#include "pixel_container.h"

#ifndef IMAGE_STREAM_H_
#define IMAGE_STREAM_H_

class ImageStream : public AbstractStream {
private:
	string m_path;
	vector<pixel_container> m_data;
	string m_stream_name;
	string m_hash;
	SDL_Surface* m_img;
	SDL_PixelFormat* m_pixel_format;
	Uint16 m_width;
	Uint16 m_height;
	Uint8 m_bpp;
	bool m_null_pixel_present;
	
	/*
	 * Takes pixels contained in an RGB container and fills up a DataChunk with them.
	 * @d: DataChunk to be filled up.
	 * @buffer: RGB container that contains pixels.
	 * @returns: DataChunk filled up.
	 */
	MemDataChunk& fill_up_DataChunk (MemDataChunk* d, pixel_container* buffer) const;
	

	
	/*
	 * Sets a pixel of a surface in x,y position.
	 * @pixel_format: pixel properties.
	 * @position: surface's first pixel position.
	 * @pitch: pitch of surface.
	 * @x: orizontal position.
	 * @y: vertical position.
	 * @pixel: contains pixel color components.
	 */
	void set_pixel (SDL_PixelFormat* pixel_format, void* position, Uint16 pitch, Uint16 x, Uint16 y, pixel_container pixel) const;
	
	/*
	 * Gets a pixel from a surface.
	 * @x: orizontal position.
	 * @y: vertical position.
	 * @returns: pixel container containing color components.
	 */
	pixel_container get_pixel(Uint16 x, Uint16 y);
	
	/*
	 * Calculates a position by an initial point in stream and a reference direction.
	 * @current_position: position of current pixel.
	 * @direction: reference direction.
	 * @returns: final position by moving in direction.
	 * 
	 * north direction = 1;
	 * south direction = 2;
	 * east direction = 3;
	 * west direction = 4;
	 */
	Uint32 calculate_position(Uint32 current_position, Uint8 direction, pixel_container pc);
	
	/*
	 * Sets color component for a pixel contained in stream.
	 * @position: position in stream to be filled.
	 * @r: red color component.
	 * @g: green color component.
	 * @b: blue color component.
	 */
	void set_pixel_in_data(Uint32 position, Uint8 r, Uint8 g, Uint8 b);
	
public:
	ImageStream();

	/*
	 * Get a data set from a file.
	 * @dimension: number of single data
	 * @returns: a data chunk containing data set
	 */
	MemDataChunk& get_data(Uint16 dimension) const;

	/*
	 * Get parts of a text stream, specifying size and starting from offset.
	 * @param offset: starting point
	 * @param size: data size
	 * @returns: a data chunk containing data selected
	 */
	MemDataChunk& get_data(Uint64 offset, Uint64 size) const;

	/*
	 * Get data dimension.
	 * @returns: data set dimension
	 */
	Uint32 get_data_dim() const;

	/*
	 * Set stream name.
	 * @name: stream name
	 */
	void set_stream_name(string& name);

	/*
	 * Get stream name.
	 * @returns: stream name
	 */
	string get_stream_name() const;

	/*
	 * Get stream hash.
	 * @returns: hash code calculated on stream content
	 */
	string compute_hash_md5() const;

	/*
	 * Saves a stream to disk.
	 * @path: filesystem path of file to save;
	 * @returns: true if operation is successful
	 */
	bool save_to_disk(const string& path) const;

	/*
	 * Insert data to the current stream.
	 * @data: data to be added;
	 */
	void set_data(const MemDataChunk& data);

	~ImageStream();
	
	/*
	 * Loads a stream from disk.
	 * @path: filesystem path of file to load;
	 * @returns: true if operation is successful
	 */
	bool load_from_disk(const string& path);

	/*
	 * Serialize an image data stream into a DataChunk.
	 * @returns: Datachunk serialized
	 */
	MemDataChunk& serialize() const;
	
	/*
	 * Deserialize a DataChunk to an image data stream.
	 */
	bool deserialize(const IDataChunk*);
	
	/*
	 * Gets bits number per pixel.
	 * @returns: bits number.
	 */
	Uint8 get_bits_per_pixel();
	
	/*
	 * Sets bits number per pixel.
	 * @bpp: bits number per pixel.
	 */
	void set_bits_per_pixel(Uint8 bpp);
	
	/*
	 * Gets source image width.
	 * @returns: width.
	 */
	Uint16 get_width();
	
	/*
	 * Gets source image height.
	 * @returns: height.
	 */
	Uint16 get_height();
	
	/*
	 * Sets image width.
	 * @width: image width.
	 */
	void set_width(Uint16 width);
	
	/*
	 * Sets image height.
	 * @height: image height.
	 */
	void set_height(Uint16 height);
	
	/*
	 * Interpolates null pixels color values.
	 */
	void interpolate_pixels(pixel_container pc);
	
	/*
	 * Gets null pixel presence in stream.
	 * @returns: true if null pixel is present, false otherwise.
	 */
	bool get_null_pixel_presence();
	
	/*
	 * Sets null pixel presence in stream.
	 * @presence: null pixel presence.
	 */
	void set_null_pixel_presence(bool presence);
};

#endif /*IMAGE_STREAM_H_*/
