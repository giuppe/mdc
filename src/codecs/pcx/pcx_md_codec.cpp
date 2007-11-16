/***************************************************************************
           pcx_md_codec.cpp  - Menage PCX codec
                             -------------------
    begin                : Oct 31, 2007
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



#include "pcx_md_codec.h"
#include <string>
#include "defs.h"
#include "pcx_stream.h"
#include "../md_stream.h"
#include "../descriptor.h"
#include "../../common/data_chunk.h"
#include "pcx_codec_parameters.h"
#include <vector>
#include <cmath>

PcxMDCodec::PcxMDCodec() {
	m_seq_counter.push_back(0);
	m_flows_number = 2;
	m_preferred_payload_size = 50000;
}


void PcxMDCodec::code(AbstractStream* stream, MDStream* md_stream) {
	
	
	Uint32 stream_size = stream->get_data_dim();
	Uint32 flow_dimension = (stream_size/m_flows_number)+1;
	
	Uint32 descriptors_number = (Uint32)ceil(((double)flow_dimension)/((double)m_preferred_payload_size));
	Uint16 max_payload_size = (flow_dimension/descriptors_number)+1;
	md_stream->init(m_flows_number, descriptors_number);
	
	PcxCodecParameters* pcp = new PcxCodecParameters();
	pcp->extractPcxCodecParameters(stream);
	DEBUG_OUT("descriptors_number: "<<descriptors_number<<"\n");
	DEBUG_OUT("m_flows_number: "<<m_flows_number<<"\n");
	

	// start from 128byte
	
	
	Uint64 offset = 128;
	for (Uint8 i=0; i<m_flows_number; i++) {
		offset= 128;
		DEBUG_OUT("FLOW: "<<i<<"\n");
		for (Uint32 j=0; j<descriptors_number; j++) {
			if (stream_size-offset > 0 || i<m_flows_number ) {
				Descriptor* descriptor= new Descriptor();
				descriptor->set_hash(stream->get_stream_hash());
				descriptor->set_file_name(stream->get_stream_name()+".mdc");
				descriptor->set_flow_id(i);
				descriptor->set_sequence_number(j);
				descriptor->set_codec_name(std::string("pcx"));
				descriptor->set_codec_parameter(pcp);
				Uint16 payload_size;
				if (stream_size-offset-1 < max_payload_size)
				{
					payload_size = stream_size - offset;
				}
				else
				{
					payload_size = max_payload_size;
				}
				
				DataChunk payload;
				DEBUG_OUT("offset: "<<(Uint32 (offset))<<"\n");
				DEBUG_OUT("payload_size: "<<payload_size<<"\n");
				
				// partire da 128byte
				
				Uint32 v=i;
				DEBUG_OUT("DATA_DIM: "<<(Uint32 (stream->get_data_dim() - pcp->get_size()))<<"\n");
			
				
				for(Uint32 k = 0; k < (stream->get_data_dim() - pcp->get_size()); ){
					DataChunk& p_data = stream->get_data(offset, (( pcp->get_bytes_per_line() * 3 ) + 2));
					Uint8* b_data = p_data.get_data();
					DEBUG_OUT("LENGHT: "<<p_data.get_lenght()<<"\n");
					Uint8 l = 0;
					Uint8 spago = l;
					for(; l < (spago+pcp->get_bytes_per_line()+1);  l++ ){
						if(b_data[l] != 193){
							if(v%m_flows_number == 0){
								payload+=(stream->get_data(offset, 1));
								//DEBUG_OUT("\t\tpixel[red]:\t"<<b_data[l]<<"\n");
							}
							v++;
						}else{
							payload+=(stream->get_data(offset, 1));
						}
						offset++;
						k++;
					}

					spago=l;
					v++;
					for(; l < (spago+pcp->get_bytes_per_line());  l++ ){
						if(b_data[l] != 193){
							if(v%m_flows_number == 0){
								payload+=(stream->get_data(offset, 1));
								//DEBUG_OUT("\t\tpixel[green]:\t"<<b_data[l]<<"\n");
							}
							v++;
						}else{
							payload+=(stream->get_data(offset, 1));
						}
						offset++;
						k++;
					}
					spago=l;
					v++;
					for(; l < (spago+pcp->get_bytes_per_line()+1);  l++ ){
						if(b_data[l] != 193){
							if(v%m_flows_number == 0){
								payload+=(stream->get_data(offset, 1));
								//DEBUG_OUT("\t\tpixel[blue]:\t"<<b_data[l]<<"\n");
							}
							v++;
						}else{
							payload+=(stream->get_data(offset, 1));
						}
						offset++;
						k++;
					}


				}
	
				descriptor->set_payload(payload);
				md_stream->set_descriptor(descriptor);
			}
		}
	}

}

void PcxMDCodec::decode(const MDStream* md_stream, AbstractStream* stream) {
	DEBUG_OUT("DECODE\n");
	if (!md_stream->is_empty()) {
		std::string name;
		DataChunk* dc = new DataChunk();
		for (Uint8 i=0; i<md_stream->get_flows_number(); i++)
			for (Uint32 j=0; j<md_stream->get_sequences_number(); j++) {
				Descriptor* descriptor = new Descriptor();
				if (md_stream->get_descriptor(i, j, descriptor) && (descriptor->get_codec_name()=="text")) {
					name = descriptor->get_file_name();
					if (md_stream->is_valid(descriptor->get_flow_id(), descriptor->get_sequence_number()))
						(*dc) += *(descriptor->get_payload());
				}
			}
		stream->set_stream_name(name);
		stream->update_stream_hash();
		stream->set_data(*dc);
	}
}

PcxMDCodec::~PcxMDCodec() {}

void PcxMDCodec::set_flows_number (Uint8 number) {
	if ((number>0) || (number<65))
	{
		m_flows_number = number;
	}
	else
	{
		LOG_ERROR("Trying to set flows number to "<<number<<">64 (Max flows number for PcxMDCodec)");
	}
}

void PcxMDCodec::set_preferred_payload_size (Uint16 size) {
	if ((size>25) || (size<55000))
	{
		m_preferred_payload_size = size;
	}
	else
	{
		LOG_ERROR("Trying to set preferred payload to "<<size<<": for PcxMDCodec should be in range [25,55000]");
	}
}
