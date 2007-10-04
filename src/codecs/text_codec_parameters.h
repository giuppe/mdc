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
#ifndef TEXT_CODEC_PARAMETERS_H_
#define TEXT_CODEC_PARAMETERS_H_

class TextCodecParameters : public Serializable {
protected:
	Uint32 m_file_size;
	Uint8 m_sequence_number;
	string m_file_name;
public:
	DataChunk& serialize() = 0;
	virtual void deserialize(const DataChunk&)= 0;
	virtual ~MpegCodecParameters(){};
};

#endif /*TEXT_CODEC_PARAMETERS_H_*/
