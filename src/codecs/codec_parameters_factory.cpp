#include "defs.h"
#include "codec_parameters_factory.h"
#include "text/text_codec_parameters.h"
#include "pcx/pcx_codec_parameters.h"

AbstractCodecParameters* CodecParametersFactory::create_codec_parameters(std::string codec_name)
{
	if(codec_name=="text")
	{
		return new TextCodecParameters();
	}
	else if(codec_name=="pcx")
	{
		return new PcxCodecParameters();
	}
	LOG_FATAL_STATIC("Unable to manage codec parameters of type: "<<codec_name);
	exit(1);
	
	return NULL;
}
