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

ImageStream::ImageStream() {m_data.resize(0);}

bool ImageStream::load_from_disk(const string& path) {
	
	// Prototype code //
	
	/* Load the BMP file into a surface */
	m_img = SDL_LoadBMP(path.c_str());
	m_pixel_format = m_img->format;
	/* Lock the surface */
	SDL_LockSurface(m_img);
	/* Get the topleft pixel */
	SDL_Color color;
	Uint8 index;
	index = *(Uint8 *)m_img->pixels;
	color = m_pixel_format->palette->colors[index];
	
	// Old standard code //
	
	if (path.size() > 0) {
		m_stream_name = path.substr(path.find_last_of("/")+1, path.find_last_of("."));		
		AbstractDirectory* dir = DirectoryFactory::createDirectory();
		DataChunk dc;
		if (dir->load_file(path, dc)) {
			deserialize(dc);
			return true;
		}
	}
	return false;
	
	//add (or substitute) SDL commands to load an image from disk to a complex type.
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
	for(Uint64 i=0; i<size; i++)
		buffer[i]=m_data[offset+i];
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
	Uint8* buffer = new Uint8[m_data.size()];
	for (Uint32 i=0; i<m_data.size(); i++)
		buffer[i]= m_data[i];
	Uint32 size = m_data.size();
	dc->append(size, buffer);
	return *dc;			
}

void ImageStream::deserialize(const DataChunk& datachunk) {
	DataChunk dc;
	dc += datachunk;
	while (dc.get_lenght() > 0) {
		Uint8 curr_char;
		dc.extract_head(curr_char);
		m_data.push_back((Sint8)curr_char);
	}
}

string ImageStream::compute_hash_md5() const {
	return Hash::md5_from_datachunk(this->serialize());
}

ImageStream::~ImageStream() {}

void ImageStream::set_data (DataChunk& data) {
	Uint32 real_data_size = data.get_lenght();
	m_data.resize(real_data_size);
	Uint8* real_data = data.get_data();
	for (Uint32 i=0; i<data.get_lenght(); i++)
		m_data[i] = real_data[i];
}

Uint8 ImageStream::get_bits_per_pixel() {return m_pixel_format->BitsPerPixel;}
