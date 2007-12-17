
#include "defs.h"
#include "data_chunk_iterator.h"
#include "i_data_chunk.h"
#include "mem_data_chunk.h"
#include <SDL/SDL_net.h>

bool DataChunkIterator::get_data(Uint32 lenght, Uint8*& data)
{
	bool result = m_data->get_data(m_position, lenght, data);
	if(result == true)
	{
		m_position+=lenght;
	}
	return result;
}

bool DataChunkIterator::has_next()
{
	return m_position < m_data->get_lenght();
}

bool DataChunkIterator::get_Uint32(Uint32& data)
{
	Uint8* new_data;
	bool result = get_data(4, new_data);
	if(result == true)
	{
		data = SDLNet_Read32(new_data);
		delete new_data;
	}
	return result;
}

bool DataChunkIterator::get_Sint32(Sint32& data)
{
	Uint8* new_data;
	bool result = get_data(4, new_data);
	if(result == true)
	{
		data = (Sint32)SDLNet_Read32(new_data);
		delete new_data;
	}
	return result;
}


bool DataChunkIterator::get_Uint16(Uint16& data)
{
	Uint8* new_data;
	bool result = get_data(2, new_data);
	if(result == true)
	{
		data = SDLNet_Read16(new_data);
		delete new_data;
	}
	return result;
}
	
bool DataChunkIterator::get_Sint16(Sint16& data)
{
	Uint8* new_data;
	bool result = get_data(2, new_data);
	if(result == true)
	{
		data = (Sint16)SDLNet_Read16(new_data);
		delete new_data;
	}
	return result;
}
	
bool DataChunkIterator::get_Uint8(Uint8& data)
{
	Uint8* new_data;
	bool result = get_data(1, new_data);
	if(result == true)
	{
		data = *new_data;
		delete new_data;
	}
	return result;
}
		
bool DataChunkIterator::get_Sint8(Sint8& data)
{
	Uint8* new_data;
	bool result = get_data(1, new_data);
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
bool DataChunkIterator::get_cstring(char* &data)
{
	Uint8* new_data;
	Uint32 null_position;
	if(!m_data->find_null(m_position, null_position))
	{
		return false;
	}
	
	Uint32 new_lenght = null_position - m_position;
	
	bool result =  get_data(new_lenght, new_data);
	
	if(result == true)
	{
		data = new char[new_lenght];
		memcpy(data, new_data, new_lenght);
		//delete [] new_data;
	}
	//remove the terminating null
	m_position++;
	return result;
}

bool DataChunkIterator::get_data_chunk(Uint32 lenght, IDataChunk*& data)
{
	data = new MemDataChunk();
	Uint8* buffer;
	if(!this->get_data(lenght, buffer))
	{
		return false;
	}
	data->append_data(lenght, buffer);
	return true;
}

