
#include "defs.h"
#include "file_data_chunk.h"
#include "../hash/hash.h"


void FileDataChunk::open_file()
{
	close_file();
	
	m_file = fopen(m_path.c_str(), "ab+");
	if (m_file == NULL) 
	{
		LOG_ERROR("Unable to open file "<<m_path);
		m_is_open_file = false;
		return;
	}
	
	m_is_open_file =true;
}

Uint32 FileDataChunk::get_lenght() const
{
	if(m_is_open_file==false)
	{
			LOG_ERROR("File "<<m_path<<" is not open.");
			return false;
	}

	Uint32 lSize=0;
			fseek (m_file , 0 , SEEK_END);
			lSize = ftell (m_file);
			rewind (m_file);
			return lSize;
}

FileDataChunk::~FileDataChunk()
{
	close_file();
}

const char* FileDataChunk::compute_hash_md5() const
{
	return Hash::md5_from_file(m_path).c_str();
}


void FileDataChunk::append_data(Uint32 lenght, Uint8* data)
{
	if(m_is_open_file==false)
	{
			LOG_ERROR("File "<<m_path<<" is not open.");
			return;
	}
		

	
	fseek (m_file , 0 , SEEK_END);
	
	fwrite(data, lenght, 1, m_file);
	
	rewind (m_file);
}

void FileDataChunk::erase()
{

	close_file();
	remove(m_path.c_str());
	open_file();
}

void FileDataChunk::close_file()
{
	if(m_is_open_file!=true)
	{
		return;
	}

	fclose(m_file);
	m_is_open_file = false;
	
}

bool FileDataChunk::get_data(Uint32 offset, Uint32 lenght, Uint8*& data) const
{
	if(m_is_open_file==false)
	{
		LOG_ERROR("File "<<m_path<<" is not open.");
		return false;
	}

	
	if(lenght==0)
	{
		LOG_ERROR("Invalid zero lenght.");
		return false;
	}
	
	Uint8* buffer = new Uint8[lenght];

	fseek(m_file, offset, SEEK_SET);
	Uint32 read_lenght = fread(buffer, lenght, 1, m_file);
	if(read_lenght!=1)
	{
		LOG_ERROR("Trying to read outside range: "<<read_lenght<<"!=1");
		return false;
	}
	data = buffer;
	return true;

}


bool FileDataChunk::open(string path)
{
	m_path = path;

	open_file();
	return m_is_open_file;
}

bool FileDataChunk::find_null(Uint32 offset, Uint32& position) const
{
	if(!m_is_open_file)
	{
		return false;
	}
	Uint32 count = 0;
	fseek(m_file, offset, SEEK_SET);
	char ch = getc(m_file);
	if(feof(m_file)!=0)
	{
		return false;
	}
	while(ch != 0)
	{
		count++;
		ch = getc(m_file);
		if(feof(m_file)!=0)
		{
			return false;
		}
	}
	position = offset + count;
	return true;
}

