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
public:
	DataChunk& serialize() {
		DataChunk* dc = new DataChunk;
		return dc;
	}
	
	void deserialize(const DataChunk&) {};
	~TextCodecParameters(){};
};

#endif /*TEXT_CODEC_PARAMETERS_H_*/
