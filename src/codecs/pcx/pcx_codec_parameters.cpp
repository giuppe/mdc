/***************************************************************************
           pcx_codec_parameters.h  -  PCX Codec Parameters class
                             -------------------
    begin                : Oct 31 2007
    copyright            : Ivan Coppa
    email                : ivan.coppa@gmail.com
 ***************************************************************************/

/***************************************************************************
 *                                                                                                                 
 *   This program is free software; you can redistribute it and/or modify  
 *   it under the terms of the GNU General Public License, Version 2,        
 *   as published by the Free Software Foundation.                                  
 *                                                                                                                 
 ***************************************************************************/
 
 
#include "pcx_codec_parameters.h"
#include "../../common/data_chunk.h"
#include "../../common/serializable.h"
#include "pcx_stream.h"


#include <cassert>

PcxCodecParameters::PcxCodecParameters() 
{
	m_size = 128;
}

void PcxCodecParameters::extractPcxCodecParameters(AbstractStream* stream)
{
	sdata = stream->get_data(0,127); // prendo
	Uint8* m_data = sdata.get_data();
	m_bytes_per_line = m_data[66];
	for(Uint8 i=0; i < sdata.get_lenght(); i++){
		m_headerinfo[i] = m_data[i];
		//DEBUG_OUT(i<<":\t"<<m_headerinfo[i]<<"\n");
	}
}




Uint8 PcxCodecParameters::get_bytes_per_line() const
{
	return m_bytes_per_line;
}




Uint32 PcxCodecParameters::get_size() const
{
	return m_size;
}




DataChunk& PcxCodecParameters::serialize() const 
{
	DEBUG_OUT("SERIALIZE: data_lenght: "<<sdata.get_lenght()<<"\n");
	DataChunk* dc = new DataChunk;
	for(Uint8 i=0; i < 128 ; i++){
		dc->append(m_headerinfo[i]);
		//DEBUG_OUT(i<<":\t"<<m_headerinfo[i]<<"\n");
	}
	return *dc;
}

void PcxCodecParameters::deserialize(const DataChunk& dc)
{
	assert(!"This function is a stub.");
}

PcxCodecParameters::~PcxCodecParameters() {}
