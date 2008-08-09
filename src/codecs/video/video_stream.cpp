/***************************************************************************
                    video_stream.cpp  -  Insert video stream
                             -------------------
    begin                : May 7, 2008
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

#include "video_stream.h"
#include "defs.h"
#include "../../common/data/mem_data_chunk.h"
#include "../../common/dir/abstract_directory.h"
#include "../../common/dir/directory_factory.h"
#include "../../common/hash/hash.h"
#include "../image/pixel_container.h"
#include "ffmpeg/avcodec.h"
#include "ffmpeg/avformat.h"
#include <cmath>

VideoStream::VideoStream() {
	m_data.resize(0);
	m_flow.resize(0);
	m_width = 0;
	m_height = 0;
	m_null_pixel_present = false;
	m_last_frame_number = 0;
	av_register_all();
	m_bitrate = 0;
	m_gop_size = 0;
}

pixel_container VideoStream::get_pixel(AVFrame* frame, Uint16 x, Uint16 y) {
	Uint8* p = (Uint8*)frame->data[0]+(y*frame->linesize[0])+(x*3);
	pixel_container pc;
	if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
		pc.set_r(p[2]);
		pc.set_g(p[1]);
		pc.set_b(p[0]);
	}
	else {
		pc.set_r(p[0]);
		pc.set_g(p[1]);
		pc.set_b(p[2]);
	}
	return pc;
}

bool VideoStream::load_from_disk(const string& path) {
	if (path.size() <= 0) return false;
	m_stream_name = path.substr(path.find_last_of("/")+1, path.find_last_of("."));
	m_path = path;
	m_data.clear();
	get_video_stream(path);
	return true;
}

bool VideoStream::save_to_disk(const string& path) const {}
void VideoStream::set_pixel (SDL_PixelFormat* pixel_format, void* position, Uint16 pitch, Uint16 x, Uint16 y, pixel_container pixel) const {}

MemDataChunk& VideoStream::get_data(Uint64 offset, Uint64 size) const {
	MemDataChunk* d = new MemDataChunk();
	pixel_container buffer;
	for (Uint64 i=0; i<size; i++)
	{
		MemDataChunk* curr_data = &(m_data[offset+i].serialize()); 
		(*d)+= curr_data;
		delete curr_data;
	}
	return *d;
}

MemDataChunk& VideoStream::fill_up_DataChunk (MemDataChunk* d, pixel_container* buffer) const {}
Uint32 VideoStream::get_data_dim() const {}
void VideoStream::set_stream_name(string& name) {}
string VideoStream::get_stream_name() const {return m_stream_name;}

MemDataChunk& VideoStream::serialize() const {
	MemDataChunk* dc = new MemDataChunk();
	pixel_container buffer;
	for (Uint32 i=0; i<m_data.size(); i++)
		(*dc) += &(m_data[i].serialize());
	return *dc;
}

bool VideoStream::deserialize(const IDataChunk* datachunk) {}
string VideoStream::compute_hash_md5() const {}
VideoStream::~VideoStream() {}
void VideoStream::set_data (const MemDataChunk& data) {}
Uint8 VideoStream::get_bits_per_pixel() {return 24;}
Uint16 VideoStream::get_width() {return m_width;}
Uint16 VideoStream::get_height() {return m_height;}
void VideoStream::set_width(Uint16 width) {m_width = width;}
Uint32 VideoStream::get_last_frame_number() {return m_last_frame_number;}
void VideoStream::set_height(Uint16 height) {m_height = height;}
void VideoStream::set_bits_per_pixel(Uint8 bpp) {m_bpp = bpp;}
bool VideoStream::get_null_pixel_presence() {return m_null_pixel_present;}
void VideoStream::set_null_pixel_presence(bool presence) {m_null_pixel_present = presence;}

void VideoStream::get_video_stream(std::string path) {
	char* char_path = new char[path.max_size()];
	path.copy(char_path, path.size());
	AVFormatContext* p_format_ctx;
	if (av_open_input_file(&p_format_ctx, char_path, NULL, 0, NULL) != 0) {
		LOG_ERROR("Could not open file: "+path);
		return;
	}
	if (av_find_stream_info(p_format_ctx) < 0) {
		LOG_ERROR("Couldn't find stream information.");
		return;
	}
	//dump_format(p_format_ctx, 0, char_path, false); //Print file content informations
	delete [] char_path;
	bool found_video_stream = false;
	Uint8 video_stream;
	for (video_stream=0; video_stream<p_format_ctx->nb_streams; video_stream++)
		if (p_format_ctx->streams[video_stream]->codec->codec_type == CODEC_TYPE_VIDEO) {
			found_video_stream = true;
			break;
		}
	if (!found_video_stream) {
		LOG_ERROR("Didn't find a video stream.");
		return;
	}
	AVCodecContext* p_codec_ctx = p_format_ctx->streams[video_stream]->codec;
	m_bitrate = p_codec_ctx->bit_rate;
	m_gop_size = p_codec_ctx->gop_size;
	AVCodec* p_codec = avcodec_find_decoder(p_codec_ctx->codec_id);
	if (p_codec == NULL) {
		LOG_ERROR("Codec not found.");
		return;
	}
	if (p_codec->capabilities & CODEC_CAP_TRUNCATED)
		p_codec_ctx->flags|=CODEC_FLAG_TRUNCATED;
	if (avcodec_open(p_codec_ctx, p_codec) < 0) {
		LOG_ERROR("Could not open codec.");
		return;
	}
	AVFrame* p_frame = avcodec_alloc_frame();
	AVFrame* p_frame_rgb = avcodec_alloc_frame();
	if (p_frame_rgb == NULL) return;
	if (p_codec_ctx->pix_fmt == 2) m_bpp = 24;
	m_width = p_codec_ctx->width;
	m_height = p_codec_ctx->height;
	Uint16 num_bytes = avpicture_get_size(PIX_FMT_RGB24, m_width, m_height);
	Uint8* buffer = new Uint8[num_bytes];	
	avpicture_fill((AVPicture*)p_frame_rgb, buffer, PIX_FMT_RGB24, m_width, m_height);
	Uint16 secs = 0;
	if (p_format_ctx->duration > 0)
		secs = p_format_ctx->duration/AV_TIME_BASE;
	while (get_next_frame(p_format_ctx, p_codec_ctx, video_stream, p_frame)) {
		img_convert((AVPicture*)p_frame_rgb, PIX_FMT_RGB24, (AVPicture*)p_frame, p_codec_ctx->pix_fmt, m_width, m_height);
		if (++m_last_frame_number <= 25) {//must be secs*25
			//LOG_INFO("Reading frame "<<m_last_frame_number<<" from disk.");
			//save_frame(p_frame_rgb, m_last_frame_number);
			for (Uint16 y=0; y<m_height; y++)
				for (Uint16 x=0; x<m_width; x++)
					m_data.push_back(get_pixel(p_frame_rgb, x, y));
		}
		else break;
	}
	delete [] buffer;
	av_free(p_frame_rgb);
	av_free(p_frame);
	avcodec_close(p_codec_ctx);
	av_close_input_file(p_format_ctx);
	return;
}

void VideoStream::save_frame(AVFrame* p_frame, Uint32 i_frame) {
	FILE *p_file;
	char sz_filename[32];
	sprintf(sz_filename, "frame%d.ppm", i_frame);
	p_file = fopen(sz_filename, "wb");
	if (p_file == NULL) {
		LOG_ERROR("I/O error!");
		return;
	}
	fprintf(p_file, "P6\n%d %d\n255\n", m_width, m_height);
	for (Uint16 y=0; y<m_height; y++)
		fwrite(p_frame->data[0]+y*p_frame->linesize[0], 1, m_width*3, p_file);
	fclose(p_file);
}

bool VideoStream::get_next_frame(AVFormatContext* p_format_ctx, AVCodecContext* p_codec_ctx, Uint8 video_stream, AVFrame* p_frame) {
	static AVPacket packet;
	static Uint64 bytes_remaining = 0;
	static Uint8* raw_data;
	static bool f_first_time = true;
	Uint32 bytes_decoded;
	int frame_finished;
	if (f_first_time) {
		f_first_time = false;
		packet.data = NULL;
	}
	while (true) {
		while (bytes_remaining > 0) {
			bytes_decoded = avcodec_decode_video(p_codec_ctx, p_frame, &frame_finished, raw_data, bytes_remaining);
			if (bytes_decoded < 0) {
				LOG_ERROR("Error while decoding frame.\n");
				return false;
			}
			bytes_remaining -= bytes_decoded;
			raw_data += bytes_decoded;
			if (frame_finished) return true;
		}
		do {
			if (packet.data != NULL) av_free_packet(&packet);
			if (av_read_packet(p_format_ctx, &packet) < 0) goto loop_exit;
		} while(packet.stream_index != video_stream);
		bytes_remaining = packet.size;
		raw_data = packet.data;
	}
	loop_exit:
	bytes_decoded = avcodec_decode_video(p_codec_ctx, p_frame, &frame_finished, raw_data, bytes_remaining);
	if (packet.data != NULL) av_free_packet(&packet);
	return (frame_finished != 0);
}

void VideoStream::save_video_stream(Uint8* stream, std::string description_number, Uint8 flows_number) {
	std::string extension = m_path.substr(m_path.find_last_of(".")+1, m_path.size());
	std::string name = m_path.substr(m_path.find_last_of("/")+1, m_path.find_last_of(".")-m_path.find_last_of("/")-1);
	std::string filename = name+"_"+description_number+"."+extension;
	AVOutputFormat* fmt = guess_format(NULL, filename.c_str(), NULL);
	AVFormatContext* format_context = av_alloc_format_context();
	format_context->oformat = fmt;
	AVStream* video_stream = av_new_stream(format_context, 0);
	AVCodecContext* video_codec_context = avcodec_alloc_context();
	video_codec_context = video_stream->codec;
	video_codec_context->codec_id = fmt->video_codec;
	video_codec_context->codec_type = CODEC_TYPE_VIDEO;
	video_codec_context->bit_rate = m_bitrate/flows_number;
	video_codec_context->time_base.den = 25;
	video_codec_context->time_base.num = 1;
	video_codec_context->gop_size = m_gop_size;
	video_codec_context->mb_decision = 2;
	video_codec_context->me_method = 1;
	video_codec_context->pix_fmt = PIX_FMT_YUV420P;	
	video_codec_context->width = m_width;
	video_codec_context->height = m_height;
	AVCodec* video_codec = avcodec_find_encoder(video_codec_context->codec_id);
	if (!video_codec) {
		LOG_ERROR("Video codec not found.\n");
		return;
	}
	if (fmt->priv_data_size > 0) {
		format_context->priv_data = av_mallocz(fmt->priv_data_size);
		if (!format_context->priv_data) {
			LOG_ERROR("Error allocating private data for format context ... aborting.\n");
			return;
		}
	}
	format_context->preload = (int)(0.5*AV_TIME_BASE);
	format_context->max_delay = (int)(0.7*AV_TIME_BASE);
	if (av_set_parameters(format_context, NULL) < 0) {
		LOG_ERROR("Invalid encoding parameters... aborting.\n");
		return;
	}
	if (avcodec_open(video_codec_context, video_codec) < 0) {
		LOG_ERROR("Could not open video codec.\n");
		return;
	}
	//dump_format(format_context, 0, filename.c_str(), 1);
	Uint32 current_description_size = 400000;
	Uint8* current_description = new Uint8[current_description_size];
	AVFrame* frame_rgb = avcodec_alloc_frame();
	if (frame_rgb == NULL) {
		LOG_ERROR("Could not allocate RGB frame.\n");
		return;
	}
	url_fopen(&format_context->pb, filename.c_str(), URL_WRONLY);	
	av_write_header(format_context);
	Uint32 frame_dimension = avpicture_get_size(PIX_FMT_RGB24, m_width, m_height)*sizeof(Uint8);
	Uint8* rgb_buffer = new Uint8[frame_dimension];
	if (!rgb_buffer) {
		LOG_ERROR("Could not allocate buffer for output RGB frame! ... aborting.\n");
		return;
	}
	for (Uint32 i=0; i<1; i++) {//must be m_last_frame_number-2
		for (Uint32 j=0; j<frame_dimension; j++)
			rgb_buffer[j] = stream[j+(i*frame_dimension)];
		avpicture_fill((AVPicture*)frame_rgb, rgb_buffer, PIX_FMT_RGB24, m_width, m_height);
		//save_frame(frame_rgb, 1);
		AVFrame* frame_yuv = avcodec_alloc_frame();
		if (frame_yuv == NULL) {
			LOG_ERROR("Could not allocate YUV frame.\n");
			return;
		}
		Uint8* yuv_buffer = new Uint8[avpicture_get_size(PIX_FMT_YUV420P, m_width, m_height)*sizeof(Uint8)];
		if (!yuv_buffer) {
			LOG_ERROR("Could not allocate buffer for output YUV frame! ... aborting.\n");
			return;
		}
		AVFrame* tmp_picture = alloc_picture(PIX_FMT_YUV420P);
		if (!tmp_picture) {
			LOG_ERROR("Could not allocate temporary frame.\n");
			return;
		}
		fill_yuv_image(tmp_picture, i);
		avpicture_fill((AVPicture*)frame_yuv, yuv_buffer, PIX_FMT_YUV420P, video_codec_context->width, video_codec_context->height);
		if (!yuv_buffer) {
			LOG_ERROR("Could not allocate buffer for encoded frame (yuv_buffer)! ... aborting.\n");
			return;
		}
		img_convert((AVPicture*)frame_yuv, PIX_FMT_RGB24, (AVPicture*)tmp_picture, PIX_FMT_YUV420P, m_width, m_height);
		Uint32 len = avcodec_encode_video(video_codec_context, current_description, current_description_size, frame_yuv);
		if (len > 0) {
			AVPacket packet;
			av_init_packet(&packet);
			if (video_codec_context->coded_frame->key_frame)
				packet.flags |= PKT_FLAG_KEY;
			packet.stream_index = video_stream->index;
			packet.data = current_description;
			packet.size = len;
			av_write_frame(format_context, &packet);
		}
		av_free(frame_yuv);
	}
	av_write_trailer(format_context);
	avcodec_close(video_codec_context);
	av_free(frame_rgb);
	av_free(current_description);
	free(rgb_buffer);
	av_free(format_context->streams[0]);
	url_fclose(&format_context->pb);
	av_free(format_context);
	delete[] stream;
}

AVFrame* VideoStream::alloc_picture(Uint8 pix_fmt) {
	AVFrame* picture = avcodec_alloc_frame();
	if (!picture) return NULL;
	Uint8* picture_buf = new Uint8[avpicture_get_size(pix_fmt, m_width, m_height)];
	if (!picture_buf) {
		av_free(picture);
		return NULL;
	}
	avpicture_fill((AVPicture*)picture, picture_buf, pix_fmt, m_width, m_height);
	return picture;
}

void VideoStream::fill_yuv_image(AVFrame* pict, Uint32 frame_index) {
	Uint16 size = m_width*m_height;
	Uint8* picture_buf = new Uint8[(size*3)/2]; /* size for YUV 420 */
	pict->data[0] = picture_buf;
	pict->data[1] = pict->data[0]+size;
	pict->data[2] = pict->data[1]+size/4;
	pict->linesize[0] = m_width;
	pict->linesize[1] = m_width/2;
	pict->linesize[2] = m_width/2;
	/* Y */
	for (Uint16 y=0; y<m_height; y++)
		for(Uint16 x=0; x<m_width; x++)
			pict->data[0][y * pict->linesize[0] + x] = x + y + frame_index * 3;
	/* Cb and Cr */
	for(Uint16 y=0; y<m_height/2; y++)
		for(Uint16 x=0; x<m_width/2; x++) {
			pict->data[1][y * pict->linesize[1] + x] = 128 + y + frame_index * 2;
			pict->data[2][y * pict->linesize[2] + x] = 64 + x + frame_index * 5;
		}
}
