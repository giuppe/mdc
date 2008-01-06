
#include "defs.h"
#include "abstract_data_chunk.h"
#include <cstring>
#include <cassert>
#include <SDL/SDL_net.h>

void AbstractDataChunk::append_Uint32(Uint32 data)
{
	Uint8* new_data = new Uint8[sizeof(Uint32)];
	SDLNet_Write32(data, new_data);
	append_data(sizeof(Uint32), new_data);
	delete [] new_data;
}

void AbstractDataChunk::append_Sint32(Sint32 data)
{
	Uint8* new_data = new Uint8[sizeof(Sint32)];
	SDLNet_Write32((Uint32)data, new_data);
	append_data(sizeof(Sint32), new_data);
	delete [] new_data;
}

void AbstractDataChunk::append_Uint16(Uint16 data)
{
	Uint8* new_data = new Uint8[sizeof(Uint16)];
	SDLNet_Write16(data, new_data);
	append_data(sizeof(Uint16), new_data);
	delete [] new_data;
}

void AbstractDataChunk::append_Sint16(Sint16 data)
{
	Uint8* new_data = new Uint8[sizeof(Sint16)];
	SDLNet_Write16((Uint16)data, new_data);
	append_data(sizeof(Sint16), new_data);
	delete [] new_data;
}

void AbstractDataChunk::append_Uint8(Uint8 data)
{
	append_data(1, &data);
}

void AbstractDataChunk::append_Sint8(Sint8 data)
{
	Uint8 new_data = (Uint8)data;
	append_data(1, &new_data);
}

void AbstractDataChunk::append_cstring(const char* data)
{
	Uint32 new_lenght = strlen(data)+1;
	Uint8* new_data = new Uint8[new_lenght];

	memcpy(new_data, data, new_lenght);

	memcpy(new_data+new_lenght-1, "\0", 1);
	
	append_data(new_lenght, new_data);
	
	delete [] new_data;
	
}


DataChunkIterator AbstractDataChunk::get_iterator() const
{
	return DataChunkIterator(this);
}

void AbstractDataChunk::operator+=(const IDataChunk* data)
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
		this->append_data(data->get_lenght(), temp);
	}
	delete[] temp;
}

