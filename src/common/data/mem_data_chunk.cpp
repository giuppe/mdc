/***************************************************************************
                  mem_data_chunk.cpp  -  MemDataChunk class
                             -------------------
    begin                : Jul 13 2007
    copyright            : (C) 2007 by Giuseppe D'Aqui'
    email                : kumber@tiscalinet.it
 ***************************************************************************/

/***************************************************************************
 *                                                                                                                 
 *   This program is free software; you can redistribute it and/or modify  
 *   it under the terms of the GNU General Public License, Version 2,        
 *   as published by the Free Software Foundation.                                  
 *                                                                                                                 
 ***************************************************************************/

#include "defs.h"
#include "mem_data_chunk.h"
#include <cstring>
#include <cassert>
#include <SDL/SDL_net.h>
#include "../hash/hash.h"
#include "/usr/include/lzo/lzo1x.h"
#include <cmath>

Uint8* MemDataChunk::get_data() const
{
	// FIXME: maybe we should return a copy of the data
	return m_data;
}

bool MemDataChunk::get_data(Uint32 offset, Uint32 lenght, Uint8* data) const
{
		
	if(m_lenght<(offset+lenght))
	{
		//LOG_ERROR("Cannot get data: offset/lenght outside range");
		return false;
	}
	
	if(lenght==0)
	{
		//LOG_ERROR("Cannot get data: lenght == 0");
		return false;
	}
	
	//data = new Uint8[lenght];
	Uint8* data_offsetted = m_data + offset;
	memcpy(data, data_offsetted, lenght);
	return true;
	
}



Uint32 MemDataChunk::get_lenght() const
{
	return m_lenght;
}

void MemDataChunk::replace_content(Uint8* data, Uint32 lenght)
{
	m_data = data;
	m_real_data = m_data;
	m_lenght = lenght;
}
 
/*
void MemDataChunk::operator +=(const MemDataChunk& data) {
	AbstractDataChunk::operator+=(&data);
}

*/

void MemDataChunk::set_data(Uint32 offset, Uint32 lenght, Uint8* data)
{
	if(offset>this->m_lenght)
		return;
	
	if(lenght == 0)
		return;
	
	if(offset+lenght > this->m_lenght)
		return;
	
	Uint8* data_offsetted = this->m_data + offset;
	memcpy(data_offsetted, data, lenght);
}

void MemDataChunk::set_Uint8(Uint32 offset, Uint8 data)
{
	set_data(offset, 1, &data);
}

void MemDataChunk::set_Sint8(Uint32 offset, Sint8 data)
{
	Uint8* new_data = (Uint8*) &data;
	set_data(offset, 1, new_data);
}

void MemDataChunk::set_Uint16(Uint32 offset, Uint16 data)
{
	Uint8* new_data = new Uint8[sizeof(Uint16)];
	SDLNet_Write16(data, new_data);
	set_data(offset, sizeof(Uint16), new_data);
	delete[] new_data;
}

void MemDataChunk::set_Sint16(Uint32 offset, Sint16 data)
{
	Uint8* new_data = new Uint8[sizeof(Sint16)];
	SDLNet_Write16((Uint16)data, new_data);
	set_data(offset, sizeof(Sint16), new_data);
	delete[] new_data;
}

void MemDataChunk::set_Uint32(Uint32 offset, Uint32 data)
{
	Uint8* new_data = new Uint8[sizeof(Uint32)];
	SDLNet_Write32(data, new_data);
	set_data(offset, sizeof(Uint32), new_data);
	delete[] new_data;
}

void MemDataChunk::set_Sint32(Uint32 offset, Sint32 data)
{
	Uint8* new_data = new Uint8[sizeof(Sint32)];
	SDLNet_Write32((Uint32)data, new_data);
	set_data(offset, sizeof(Sint32), new_data);
	delete[] new_data;
}

void MemDataChunk::append_data(Uint32 lenght, Uint8* data) {
	if(lenght==0) 
		return;
	Uint32 old_lenght = this->m_lenght; 
	resize(this->m_lenght + lenght);
	//Uint8* new_data = new Uint8[this->m_lenght+lenght];
	//if (this->m_lenght != 0)
	//	memcpy(new_data, this->m_data, this->m_lenght);
	//Uint8* second_segment = new_data + sizeof(Uint8)*(this->m_lenght);
	Uint8* second_segment = this->m_data + sizeof(Uint8)*old_lenght;
	memcpy(second_segment, data, lenght);
	//if (this->m_lenght != 0)
	//	delete []this->m_data;
	//this->m_data = new_data;
	//this->m_real_data = this->m_data;
	//this->m_lenght += lenght;
}

void MemDataChunk::resize(Uint32 new_size)
{
	if(new_size < this->m_lenght)
	{
		LOG_ERROR("Cannot shrink MemDataChunk.");
		return;
	}
	
	Uint8* new_data = new Uint8[new_size];
	if (this->m_lenght != 0)
	{
		memcpy(new_data, this->m_data, this->m_lenght);
		delete []this->m_data;
	}
			
	this->m_data = new_data;
	this->m_real_data = this->m_data;
	this->m_lenght = new_size;
}
/*
void MemDataChunk::append(Uint32 data)
{
	Uint8* new_data = new Uint8[sizeof(Uint32)];
	SDLNet_Write32(data, new_data);
	append(sizeof(Uint32), new_data);
	delete [] new_data;
}

void MemDataChunk::append(Sint32 data)
{
	Uint8* new_data = new Uint8[sizeof(Sint32)];
	SDLNet_Write32((Uint32)data, new_data);
	append(sizeof(Sint32), new_data);
	delete [] new_data;
}

void MemDataChunk::append(Uint16 data)
{
	Uint8* new_data = new Uint8[sizeof(Uint16)];
	SDLNet_Write16(data, new_data);
	append(sizeof(Uint16), new_data);
	delete [] new_data;
}

void MemDataChunk::append(Sint16 data)
{
	Uint8* new_data = new Uint8[sizeof(Sint16)];
	SDLNet_Write16((Uint16)data, new_data);
	append(sizeof(Sint16), new_data);
	delete [] new_data;
}

void MemDataChunk::append(Uint8 data)
{
	append(1, &data);
}

void MemDataChunk::append(Sint8 data)
{
	Uint8 new_data = (Uint8)data;
	append(1, &new_data);
}

void MemDataChunk::append(const char* data)
{
	Uint32 new_lenght = strlen(data)+1;
	Uint8* new_data = new Uint8[new_lenght];

	memcpy(new_data, data, new_lenght);

	memcpy(new_data+new_lenght-1, "\0", 1);
	
	append(new_lenght, new_data);
	
	delete [] new_data;
	
}
*/
bool MemDataChunk::extract_head(Uint32 lenght, Uint8* &data)
{
//	LOG_INFO("Extracting "<<lenght<<" bytes rom datachunk.")
	if(lenght==0)
		return false;
	
	if((this->m_lenght>=lenght))
	{
		data = new Uint8[lenght];
		memcpy(data, this->m_data, lenght);
		this->m_data += lenght;
		this->m_lenght -= lenght;
	//	LOG_INFO("Extracted. New chunk lenght is "<<this->m_lenght);
		return true;
	}
	else
	{
		LOG_ERROR("Cannot extract.");
		return false;
	}
	
	return true;
}


bool MemDataChunk::extract_head(Uint32& data)
{
	Uint8* new_data;
	bool result = extract_head(4, new_data);
	if(result == true)
	{
		data = SDLNet_Read32(new_data);
		delete new_data;
	}
	return result;
}

bool MemDataChunk::extract_head(Sint32& data)
{
	Uint8* new_data;
	bool result = extract_head(4, new_data);
	if(result == true)
	{
		data = (Sint32)SDLNet_Read32(new_data);
		delete new_data;
	}
	return result;
}


bool MemDataChunk::extract_head(Uint16& data)
{
	Uint8* new_data;
	bool result = extract_head(2, new_data);
	if(result == true)
	{
		data = SDLNet_Read16(new_data);
		delete new_data;
	}
	return result;
}
	
bool MemDataChunk::extract_head(Sint16& data)
{
	Uint8* new_data;
	bool result = extract_head(2, new_data);
	if(result == true)
	{
		data = (Sint16)SDLNet_Read16(new_data);
		delete new_data;
	}
	return result;
}
	
bool MemDataChunk::extract_head(Uint8& data)
{
	Uint8* new_data;
	bool result = extract_head(1, new_data);
	if(result == true)
	{
		data = *new_data;
		delete new_data;
	}
	return result;
}
		
bool MemDataChunk::extract_head(Sint8& data)
{
	Uint8* new_data;
	bool result = extract_head(1, new_data);
	if(result == true)
	{
		data = (Sint8)*new_data;
		delete new_data;
	}
	return result;
}

/**
 * Extract a null-terminated string (in char* format) from the beginning of DataChunk.
 * @param data (char*&) - this parameter will be replaced with content.
 */ 
bool MemDataChunk::extract_head(char* &data)
{
	Uint8* new_data;
	Uint32 new_lenght; // = (Uint8*)memchr(this->m_data, 0, 255)-this->m_data+1;
	if(!find_null(0, new_lenght))
	{
		return false;
	}
	
	bool result =  extract_head(new_lenght, new_data);
	if(result == true)
	{
		data = new char[new_lenght];
		memcpy(data, new_data, new_lenght);
		//delete [] new_data;
	}
	return result;
}


MemDataChunk::~MemDataChunk()
{
	if(m_lenght!=0)
		delete [] m_real_data;
}



void MemDataChunk::erase()
{
	if(m_lenght!=0)
			delete [] m_real_data;

	m_lenght=0;
}

bool MemDataChunk::extract_head(Uint32 lenght, MemDataChunk &data)
{
	data.erase();
	Uint8* buffer;
	this->extract_head(lenght, buffer);
	data.append_data(lenght, buffer);
	return true;
}

void MemDataChunk::set_data_chunk(Uint32 offset, IDataChunk* data)
{
	DataChunkIterator it = data->get_iterator();
	if(it.is_null())
	{
		LOG_ERROR("Trying to add a null data_chunk.");
		return;	
	}
	Uint8* temp = new Uint8[data->get_lenght()];
	if(it.get_data(data->get_lenght(), temp))
	{
		this->set_data(offset, data->get_lenght(), temp);
	}
	delete[] temp;
}


const char* MemDataChunk::compute_hash_md5() const
{

	return (Hash::md5_from_datachunk(*this)).c_str();
}


bool MemDataChunk::find_null(Uint32 offset, Uint32& position) const
{
	if(m_lenght<(offset))
	{
		LOG_ERROR("Cannot find null: offset/lenght outside range");
		return false;
	}
	
	Uint8* null_position = (Uint8*)memchr((this->m_data+offset), 0, 255);
	if(null_position == NULL)
	{
		return false;
	}
	position = (Uint32)(null_position - this->m_data);
	return true;
}

Uint8* MemDataChunk::get_compressed_data() {
	if (lzo_init() != LZO_E_OK) {
		LOG_ERROR("LZO initialization failed for compression procedure!\n");
	    return 0;
	}
	Uint8* working_memory = new Uint8[LZO1X_999_MEM_COMPRESS];
	Uint64 dest_size = ((Uint32)ceil(((m_lenght/1024))+1)*16)+m_lenght;
	Uint8* output_data = new Uint8[dest_size];
	lzo1x_999_compress(m_data, m_lenght, output_data, &compressed_size, working_memory);
	delete [] working_memory;
	return output_data;
}

Uint32 MemDataChunk::get_compressed_size() {return (Uint32)compressed_size;}
