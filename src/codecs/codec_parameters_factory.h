/***************************************************************************
                          codec_parameters_factory.h  -  
                             -------------------
    begin                : Nov 16 2007
    copyright            : (C) 2007 by Giuseppe D'Aqui'
    email                : kumber@tiscalinet.it
 ***************************************************************************/

/***************************************************************************
 *                                                                                                                 
 *   This program is free software; you can redistribute it and/or modify  
 *   it under the terms of the GNU General Public License, Version 2,        
 *   as published by the Free Software Foundation.                                  
 *                                                                                                                 
 ***************************************************************************/

#include "defs.h"

#include "abstract_codec_parameters.h"

#ifndef CODEC_PARAMETERS_FACTORY_H_
#define CODEC_PARAMETERS_FACTORY_H_
class CodecParametersFactory
{
public:
	static AbstractCodecParameters* create_codec_parameters(string codec_name);

};
#endif /*CODEC_PARAMETERS_FACTORY_H_*/
