/***************************************************************************
                    image_stream.cpp  -  Insert image stream
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
#include "defs.h"
#include "../../common/data_chunk.h"
#include "../../common/dir/abstract_directory.h"
#include "../../common/dir/directory_factory.h"
#include "../../common/hash/hash.h"
#include "RGB_container.h"

ImageStream::ImageStream() {m_data.resize(0);}

bool ImageStream::load_from_disk(const string& path) {
	if (path.size() > 0) {
		m_stream_name = path.substr(path.find_last_of("/")+1, path.find_last_of("."));
		m_img = SDL_LoadBMP(path.c_str());
		m_pixel_format = m_img->format;
		SDL_LockSurface(m_img);
		if (m_pixel_format->BitsPerPixel == 24)
			for (Uint16 x=0; x<Uint16(m_img->w); x++)
				for (Uint16 y=0; y<Uint16(m_img->h); y++) {
					Uint32 temp, pixel;
					Uint8 red, green, blue, alpha;
					/* Extracting color components from a 32-bit color value */
					pixel = *((Uint32*)m_img->pixels);//current pixel
					SDL_UnlockSurface(m_img);
					/* Get Red component */
					temp = pixel&m_pixel_format->Rmask; /* Isolate red component */
					temp = temp>>m_pixel_format->Rshift;/* Shift it down to 8-bit */
					temp = temp<<m_pixel_format->Rloss; /* Expand to a full 8-bit number */
					red = (Uint8)temp;
					/* Get Green component */
					temp = pixel&m_pixel_format->Gmask; /* Isolate green component */
					temp = temp>>m_pixel_format->Gshift;
					temp = temp<<m_pixel_format->Gloss;
					green = (Uint8)temp;
					/* Get Blue component */
					temp = pixel&m_pixel_format->Bmask; /* Isolate blue component */
					temp = temp>>m_pixel_format->Bshift;
					temp = temp<<m_pixel_format->Bloss;
					blue = (Uint8)temp;
					/* Get Alpha component */
					temp = pixel&m_pixel_format->Amask; /* Isolate alpha component */
					temp = temp>>m_pixel_format->Ashift;
					temp = temp<<m_pixel_format->Aloss;
					alpha = (Uint8)temp;
					RGB_container rgb;
					rgb.set_x_position(x+1);
					rgb.set_y_position(y+1);
					rgb.setRed_value(red);
					rgb.setGreen_value(green);
					rgb.setBlue_value(blue);
					m_data.push_back(rgb);
				}
		return true;
	}
	return false;
}

bool ImageStream::save_to_disk(const string& path) const {
	if (path.size()>0 && m_data.size()>0) {
		AbstractDirectory* dir = DirectoryFactory::createDirectory();
		if (dir->save_file(path, this->serialize())) return true;
	}
	return false;
}

DataChunk& ImageStream::get_data(Uint64 offset, Uint64 size) const {
	DataChunk* d = new DataChunk();
	Uint8* buffer = new Uint8[size];
//	for(Uint64 i=0; i<size; i++)
//		buffer[i]=m_data[offset+i];
	d->append(size, buffer);
	delete[] buffer;
	return *d;
}

Uint32 ImageStream::get_data_dim() const {return m_data.size();}

void ImageStream::set_stream_name(string& name) {
	if (name.size() > 0)
		m_stream_name = name;
}

string ImageStream::get_stream_name() const {return m_stream_name;}

DataChunk& ImageStream::serialize() const {
	DataChunk* dc = new DataChunk();
	RGB_container buffer;
	for (Uint32 i=0; i<m_data.size(); i++) {
		buffer = m_data[i];
		dc->append(buffer.get_x_position());
		dc->append(buffer.get_y_position());
		dc->append(buffer.getRed_value());
		dc->append(buffer.getGreen_value());
		dc->append(buffer.getBlue_value());
	}
	return *dc;			
}

void ImageStream::deserialize(const DataChunk& datachunk) {
	DataChunk dc;
	dc += datachunk;
	while (dc.get_lenght() > 0) {
		Uint8* curr_data;
		//dc.extract_head(curr_data));
		//m_data.push_back((Sint8)curr_char);
	}
}

string ImageStream::compute_hash_md5() const {
	return Hash::md5_from_datachunk(this->serialize());
}

ImageStream::~ImageStream() {
	delete m_img;
	delete m_pixel_format;
}

void ImageStream::set_data (DataChunk& data) {
	Uint32 real_data_size = data.get_lenght();
	m_data.resize(real_data_size);
	Uint8* real_data = data.get_data();
//	for (Uint32 i=0; i<data.get_lenght(); i++)
//		m_data[i] = real_data[i];
}

Uint8 ImageStream::get_bits_per_pixel() {return m_pixel_format->BitsPerPixel;}
