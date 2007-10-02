/***************************************************************************
                          data_chunk.cpp  -  DataChunk class
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
#include "data_chunk.h"
#include <cstring>
#include <SDL/SDL_net.h>




Uint8* DataChunk::get_data() const
{
	// FIXME: maybe we should return a copy of the data
	return m_data;
}




Uint32 DataChunk::get_lenght() const
{
	return m_lenght;
}




void DataChunk::set_content(Uint8* data, Uint32 lenght)
{
	m_initialized = true;
	m_data = data;
	m_real_data = m_data;
	m_lenght = lenght;
}




void DataChunk::operator +=(const DataChunk& data)
{
	append(data.m_lenght, data.m_data);
}

void DataChunk::append(Uint32 lenght, Uint8* data)
{
	LOG_INFO("Appending "<<lenght<<" bytes to datachunk.");
	Uint8* new_data = new Uint8[this->m_lenght+lenght];

	if(this->m_lenght != 0)
		memcpy(new_data, this->m_data, this->m_lenght);

	Uint8* second_segment = new_data + sizeof(Uint8)*(this->m_lenght);

	memcpy(second_segment, data, lenght);
	
	if(this->m_lenght != 0)
		delete []this->m_data;

	this->m_data = new_data;
	this->m_real_data = this->m_data;

	this->m_lenght += lenght;
	LOG_INFO("Done appending, new chunk lenght is "<<this->m_lenght);
}

void DataChunk::append(Uint32 data)
{
	Uint8* new_data = new Uint8[sizeof(Uint32)];
	SDLNet_Write32(data, new_data);
	append(sizeof(Uint32), new_data);
	delete [] new_data;
}

void DataChunk::append(Sint32 data)
{
	Uint8* new_data = new Uint8[sizeof(Sint32)];
	SDLNet_Write32((Uint32)data, new_data);
	append(sizeof(Sint32), new_data);
	delete [] new_data;
}

void DataChunk::append(Uint16 data)
{
	Uint8* new_data = new Uint8[sizeof(Uint16)];
	SDLNet_Write32(data, new_data);
	append(sizeof(Uint16), new_data);
	delete [] new_data;
}

void DataChunk::append(Sint16 data)
{
	Uint8* new_data = new Uint8[sizeof(Sint16)];
	SDLNet_Write32((Uint16)data, new_data);
	append(sizeof(Sint16), new_data);
	delete [] new_data;
}

void DataChunk::append(Uint8 data)
{
	append(1, &data);
}

void DataChunk::append(Sint8 data)
{
	Uint8 new_data = (Uint8)data;
	append(1, &new_data);
}

void DataChunk::append(const char* data)
{
	Uint32 new_lenght = strlen(data)+1;
	Uint8* new_data = new Uint8[new_lenght];

	memcpy(new_data, data, new_lenght);

	memcpy(new_data+new_lenght-1, "\0", 1);
	
	append(new_lenght, new_data);
	
	delete [] new_data;
	
}

bool DataChunk::extract_head(Uint32 lenght, Uint8* &data)
{
	LOG_INFO("Extracting "<<lenght<<" bytes rom datachunk.")
	if((lenght!=0)&&(this->m_lenght>=lenght))
	{
		data = new Uint8[lenght];
		memcpy(data, this->m_data, lenght);
		this->m_data += lenght;
		this->m_lenght -= lenght;
		LOG_INFO("Extracted. New chunk lenght is "<<this->m_lenght);
		return true;
	}
	else
	{
		LOG_ERROR("Cannot extract.");
		return false;
	}
	
	return true;
}


bool DataChunk::extract_head(Uint32& data)
{
	Uint8* new_data;
	bool result = extract_head(4, new_data);
	if(result == true)
	{
		data = SDLNet_Read32(new_data);
	}
	return result;
}

bool DataChunk::extract_head(Sint32& data)
{
	Uint8* new_data;
	bool result = extract_head(4, new_data);
	if(result == true)
	{
		data = (Sint32)SDLNet_Read32(new_data);
	}
	return result;
}


bool DataChunk::extract_head(Uint16& data)
{
	Uint8* new_data;
	bool result = extract_head(2, new_data);
	if(result == true)
	{
		data = SDLNet_Read16(new_data);
	}
	return result;
}
	
bool DataChunk::extract_head(Sint16& data)
{
	Uint8* new_data;
	bool result = extract_head(2, new_data);
	if(result == true)
	{
		data = (Sint16)SDLNet_Read16(new_data);
	}
	return result;
}
	
bool DataChunk::extract_head(Uint8& data)
{
	Uint8* new_data;
	bool result = extract_head(1, new_data);
	if(result == true)
	{
		data = *new_data;
	}
	return result;
}
		
bool DataChunk::extract_head(Sint8& data)
{
	Uint8* new_data;
	bool result = extract_head(1, new_data);
	if(result == true)
	{
		data = (Sint8)*new_data;
	}
	return result;
}

/**
 * Extract a null-terminated string (in char* format) from the beginning of DataChunk.
 * @param data (char*&) - this parameter will be replaced with content.
 */ 
bool DataChunk::extract_head(char* &data)
{
	Uint8* new_data;
	Uint32 new_lenght = (Uint8*)memchr(this->m_data, 0, 255)-this->m_data+1;
	bool result =  extract_head(new_lenght, new_data);
	if(result == true)
	{
		data = new char[new_lenght];
		memcpy(data, new_data, new_lenght);
		//delete [] new_data;
	}
	return result;
}


DataChunk::~DataChunk()
{
	if(m_lenght!=0)
		delete [] m_real_data;
}



