#include "defs.h"
#include "codec_parameters_factory.h"
#include "text/text_codec_parameters.h"
#include "image/image_codec_parameters.h"
#include "video/video_codec_parameters.h"

AbstractCodecParameters* CodecParametersFactory::create_codec_parameters(string codec_name) {
	if (codec_name == "text") return new TextCodecParameters();
	if (codec_name == "image") return new ImageCodecParameters();
	if (codec_name == "video") return new VideoCodecParameters();
	LOG_FATAL_STATIC("Unable to manage codec parameters of type: "<<codec_name);
	exit(1);
	return NULL;
}

AbstractCodecParameters* CodecParametersFactory::create_codec_parameters(Uint8 codec_code) {
	switch (codec_code) {
		case 1:
			return new TextCodecParameters();
			break;
		case 2:
			return new ImageCodecParameters();
			break;
		case 3:
			return new VideoCodecParameters();
			break;
		default:
			LOG_FATAL_STATIC("Unable to manage codec parameters of type: "<<codec_code);
			exit(1);
			return NULL;
			break;
		}
}
