
#include "defs.h"
#include "data_chunk_iterator.h"
#include "i_data_chunk.h"

bool DataChunkIterator::get_data(Uint32 lenght, Uint8*& data)
{
	return m_data->get_data(m_position, lenght, data);
}
