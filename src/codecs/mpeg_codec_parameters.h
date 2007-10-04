/***************************************************************************
                          codec_parameters.h  -  Codec Parameters abstract class
                             -------------------
    begin                : Oct 4 2007
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

#include "defs.h"
#include "../common/data_chunk.h"
#include "../common/serializable.h"
#include "string.h"
#ifndef MPEG_CODEC_PARAMETERS_H_
#define MPEG_CODEC_PARAMETERS_H_

class MpegCodecParameters : public Serializable {
protected:
	Uint32 m_size;
	Uint16 m_height_size;
	Uint16 m_width_size;
	Uint8 m_fps;
	Uint16 m_bitrate;
	char m_frame_type;
	string m_flow_id;
	Uint8 m_sequence_number;
	string m_file_name;
public:
	DataChunk& serialize() = 0;
	virtual void deserialize(const DataChunk&)= 0;
	virtual ~MpegCodecParameters(){};
};

#endif /*MPEG_CODEC_PARAMETERS_H_*/
