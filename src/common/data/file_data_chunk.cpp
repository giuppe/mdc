
#include "defs.h"
#include "file_data_chunk.h"
#include "../hash/hash.h"

FileDataChunk::FileDataChunk(string path)
{
	m_path = path;
	

	open_file();
}

void FileDataChunk::open_file()
{
	m_file = fopen(m_path.c_str(), "rw+");
	if (m_file == NULL) 
	{
		LOG_ERROR("Unable to open file "<<m_path);
		m_is_null=true;
		return;
	}
}

Uint32 FileDataChunk::get_lenght() const
{
		// obtain file size:
	Uint32 lSize=0;
			fseek (m_file , 0 , SEEK_END);
			lSize = ftell (m_file);
			rewind (m_file);
			return lSize;
}

FileDataChunk::~FileDataChunk()
{
	if(m_is_null!=true)
	{
		fclose(m_file);
	}
}

const char* FileDataChunk::compute_hash_md5() const
{
	return Hash::md5_from_file(m_path).c_str();
}


void FileDataChunk::append_data(Uint32 lenght, Uint8* data)
{
	fseek (m_file , 0 , SEEK_END);
	
	fwrite(data, lenght, 1, m_file);
	
	rewind (m_file);
}

void FileDataChunk::erase()
{
	fclose(m_file);
	remove(m_path.c_str());
	open_file();
}

bool FileDataChunk::get_data(Uint32 offset, Uint32 lenght, Uint8*& data) const
{
	if(lenght==0)
	{
		LOG_ERROR("Invalid zero lenght.");
		return false;
	}
	
	Uint8* buffer = new Uint8[lenght];

	fseek(m_file, offset, SEEK_SET);
	Uint32 read_lenght = fread(buffer, lenght, 1, m_file);
	if(read_lenght!=lenght)
	{
		LOG_ERROR("Trying to read outside range.");
		return false;
	}
	data = buffer;
	return true;

}
