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
#include "ffmpeg/allformats.h"

VideoStream::VideoStream() {
	m_data.resize(0);
	m_flow.resize(0);
	m_width = 0;
	m_height = 0;
	m_null_pixel_present = false;
	m_current_frame = NULL;
	m_frame_number = 0;
	av_register_all();
}

pixel_container VideoStream::get_pixel(Uint16 x, Uint16 y) {
	Uint8* p = (Uint8 *)m_current_frame->pixels+(y*m_current_frame->pitch)+(x*3);
	pixel_container pc;
	if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
		pc.set_r(p[0]);
		pc.set_g(p[1]);
		pc.set_b(p[2]);
	}
	else {
		pc.set_r(p[2]);
		pc.set_g(p[1]);
		pc.set_b(p[0]);
	}
	return pc;
}

bool VideoStream::load_from_disk(const string& path) {
	if (path.size() <= 0) return false;
	m_stream_name = path.substr(path.find_last_of("/")+1, path.find_last_of("."));
	m_flow.clear();
	get_video_stream(path);
	//TODO prima di proseguire è necessaria la traduzione di MPEG in immagini
	//se possibile, si devono estrarre m_pixel_format, m_bpp, m_width e m_height solo dal primo frame
	//si deve estrarre anche il frame_number e inserirlo in m_frame_number
	//poi ciclo su tutti i frames del filmato
	m_current_frame = SDL_LoadBMP(path.c_str());
	//if (m_current_frame == NULL) return false;
	m_pixel_format = m_current_frame->format;
	m_bpp = m_pixel_format->BitsPerPixel;
	if (m_pixel_format->BitsPerPixel != 24) return false;
	SDL_LockSurface(m_current_frame);
	m_width = m_current_frame->w;
	m_height = m_current_frame->h;
	m_data.clear();
	for (Uint16 y=0; y<m_height; y++)
		for (Uint16 x=0; x<m_width; x++)
			m_data.push_back(get_pixel(x, y));
	SDL_UnlockSurface(m_current_frame);
	//fine ciclo
	m_flow.push_back(m_data);
	m_path = path;
	return true;
}

bool VideoStream::save_to_disk(const string& path) const {
	if (path.size()>0 && m_flow.size()>0) {
		SDL_Surface* unit_test_pixel = SDL_LoadBMP("true_color.bmp");
		Uint16 pitch = m_width*(m_bpp/8);
		SDL_PixelFormat* pf = unit_test_pixel->format;
		//TODO ciclo (indice k) su tutti i frames contenuti in m_flow
		SDL_Surface* temp_frame = SDL_CreateRGBSurface(SDL_SWSURFACE, m_width, m_height, m_bpp, pf->Rmask, pf->Gmask, pf->Bmask, pf->Amask);
		SDL_LockSurface(temp_frame);
		Uint32 cont = 0;
		for (Uint16 i=0; i<m_height; i++)
			for (Uint16 j=0; j<m_width; j++) {
				SetPixel(temp_frame->format, temp_frame->pixels, pitch, j, i, m_data[cont]); //sostituire m_data con m_flow
				cont++;
			}
		SDL_UnlockSurface(temp_frame);
		SDL_Surface* final_frame = SDL_CreateRGBSurfaceFrom(temp_frame->pixels, m_width, m_height, m_bpp, pitch, temp_frame->format->Rmask, temp_frame->format->Gmask, temp_frame->format->Bmask, temp_frame->format->Amask);
		//controllare il formato dati richiesto dalle librerie per la codifica
		//salvataggio di flow in MPEG
		if (SDL_SaveBMP (final_frame, path.c_str()) == 0) {
			SDL_FreeSurface(temp_frame);
			SDL_FreeSurface(final_frame);
			SDL_FreeSurface(unit_test_pixel);
			return true;
		}
		else LOG_ERROR("SDL_SaveBMP failed:" << SDL_GetError());//modificare per MPEG
	}
	return false;
}

void VideoStream::SetPixel (SDL_PixelFormat* pixel_format, void* position, Uint16 pitch, Uint16 x, Uint16 y, pixel_container pixel) const {
	Uint32 col = SDL_MapRGB(pixel_format, pixel.get_r(), pixel.get_g(), pixel.get_b());
	Uint8* pPosition = (Uint8*)position;
	pPosition += (pitch*y);	//vertical shift
	pPosition += (3*x);		//orizontal shift
	memcpy (pPosition, &col, 3);
}

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


MemDataChunk& VideoStream::fill_up_DataChunk (MemDataChunk* d, pixel_container* buffer) const {
	d->append_Uint8(buffer->get_r());
	d->append_Uint8(buffer->get_g());
	d->append_Uint8(buffer->get_b());
	return *d;
}

Uint32 VideoStream::get_data_dim() const {return m_data.size();}

void VideoStream::set_stream_name(string& name) {
	if (name.size() > 0)
		m_stream_name = name;
}

string VideoStream::get_stream_name() const {return m_stream_name;}

MemDataChunk& VideoStream::serialize() const {
	MemDataChunk* dc = new MemDataChunk();
	pixel_container buffer;
	for (Uint32 i=0; i<m_data.size(); i++)
		(*dc)+=&(m_data[i].serialize());
	return *dc;			
}

bool VideoStream::deserialize(const IDataChunk* datachunk) {
	Uint32 i = 0;
	DataChunkIterator it = datachunk->get_iterator();
	pixel_container curr_pixel;
	Uint8 r,g,b;
	while (it.has_next()) {
		it.get_Uint8(r);
		it.get_Uint8(g);
		it.get_Uint8(b);	
		curr_pixel.set_r(r);
		curr_pixel.set_g(g);
		curr_pixel.set_b(b);
		m_data[i] = curr_pixel;
		i++;
	}
	return true;
}

string VideoStream::compute_hash_md5() const {
	return Hash::md5_from_file(this->m_path);
}

VideoStream::~VideoStream() 
{
	if(m_current_frame != NULL)
	{
		SDL_FreeSurface(m_current_frame);
	}
}

void VideoStream::set_data (const MemDataChunk& data) {
	Uint32 real_data_size = data.get_lenght();
	m_data.resize(real_data_size/3);
	deserialize(&data);
}

Uint8 VideoStream::get_bits_per_pixel() {return m_pixel_format->BitsPerPixel;}
Uint16 VideoStream::get_width() {return m_width;}
Uint16 VideoStream::get_height() {return m_height;}
void VideoStream::set_width(Uint16 width) {m_width = width;}
void VideoStream::set_height(Uint16 height) {m_height = height;}
Uint32 VideoStream::get_frame_number() {return m_frame_number;}
void VideoStream::set_frame_number(Uint32 number) {m_frame_number = number;}


void VideoStream::set_bits_per_pixel(Uint8 bpp) {m_bpp = bpp;}

void VideoStream::interpolate_pixels(pixel_container pc) {
	if (m_data.size() == 0) return;
	Uint8 new_r;
	Uint8 new_g;
	Uint8 new_b;
	for (Uint32 i=0; i<m_data.size(); i++)
		if (((m_data[i].get_r()==pc.get_r())||(m_data[i].get_r()==0)) && ((m_data[i].get_g()==pc.get_g())||(m_data[i].get_g()==0)) && ((m_data[i].get_b()==pc.get_b())||(m_data[i].get_b()==0))) {
			if (i%m_width == 0) { 									//pixels on extreme left
				new_r = m_data[calculate_position(i, 3, pc)].get_r();
				new_g = m_data[calculate_position(i, 3, pc)].get_g();
				new_b = m_data[calculate_position(i, 3, pc)].get_b();
				set_pixel_in_data(i, new_r, new_g, new_b);
			}
			else if (i == Uint32(m_width-1)) { 						//pixels on extreme right
				new_r = m_data[calculate_position(i, 4, pc)].get_r();
				new_g = m_data[calculate_position(i, 4, pc)].get_g();
				new_b = m_data[calculate_position(i, 4, pc)].get_b();
				set_pixel_in_data(i, new_r, new_g, new_b);
			}
			else if ((i>0) && (i<Uint32(m_width-1))) { 				//pixels on first row
				new_r = m_data[calculate_position(i, 2, pc)].get_r();
				new_g = m_data[calculate_position(i, 2, pc)].get_g();
				new_b = m_data[calculate_position(i, 2, pc)].get_b();
				set_pixel_in_data(i, new_r, new_g, new_b);
			}
			else if (Uint32(i/m_width)+1 == Uint32(m_height-1)) {	//pixels on last row
				new_r = m_data[calculate_position(i, 1, pc)].get_r();
				new_g = m_data[calculate_position(i, 1, pc)].get_g();
				new_b = m_data[calculate_position(i, 1, pc)].get_b();
				set_pixel_in_data(i, new_r, new_g, new_b);
			}
			else {
				new_r = (m_data[calculate_position(i, 1, pc)].get_r()+m_data[calculate_position(i, 2, pc)].get_r()+m_data[calculate_position(i, 3, pc)].get_r()+m_data[calculate_position(i, 4, pc)].get_r())/4;
				new_g = (m_data[calculate_position(i, 1, pc)].get_g()+m_data[calculate_position(i, 2, pc)].get_g()+m_data[calculate_position(i, 3, pc)].get_g()+m_data[calculate_position(i, 4, pc)].get_g())/4;
				new_b = (m_data[calculate_position(i, 1, pc)].get_b()+m_data[calculate_position(i, 2, pc)].get_b()+m_data[calculate_position(i, 3, pc)].get_b()+m_data[calculate_position(i, 4, pc)].get_b())/4;
				set_pixel_in_data(i, new_r, new_g, new_b);
			}
		}
}

Uint32 VideoStream::calculate_position (Uint32 current_position, Uint8 direction, pixel_container pc) {
	Uint32 final_position = current_position;
	switch (direction) {
	case 4: // west direction
		if ((m_data[current_position-1].get_r()!=pc.get_r()) || (m_data[current_position-1].get_g()!=pc.get_g()) || (m_data[current_position-1].get_b()!=pc.get_b()))
			final_position--;
		else final_position -= 2;
		break;
	case 3: // east direction
		if ((m_data[current_position+1].get_r()!=pc.get_r()) || (m_data[current_position+1].get_g()!=pc.get_g()) || (m_data[current_position+1].get_b()!=pc.get_b()))
			final_position++;
		else final_position += 2;
		break;
	case 1: // north direction
		if ((m_data[current_position-m_width].get_r()!=pc.get_r()) || (m_data[current_position-m_width].get_g()!=pc.get_g()) || (m_data[current_position-m_width].get_b()!=pc.get_b()))
			final_position -= m_width;
		else final_position -= m_width-1;
		break;
	case 2: // south direction
		if (current_position+m_width < Uint32(m_width*m_height)) {
			if ((m_data[current_position+m_width].get_r()!=pc.get_r()) || (m_data[current_position+m_width].get_g()!=pc.get_g()) || (m_data[current_position+m_width].get_b()!=pc.get_b()))
				final_position += m_width;
			else final_position += m_width+1;
		}
		break;
	default:
		break;
	}
	return final_position;
}

bool VideoStream::get_null_pixel_presence() {return m_null_pixel_present;}
void VideoStream::set_null_pixel_presence(bool presence) {m_null_pixel_present = presence;}

void VideoStream::set_pixel_in_data(Uint32 position, Uint8 r, Uint8 g, Uint8 b) {
	m_data[position].set_r(r);
	m_data[position].set_g(g);
	m_data[position].set_b(b);
}

void VideoStream::get_video_stream(string path) {
	AVFormatContext* pFormatCtx;
	if (av_open_input_file(&pFormatCtx, path.c_str(), NULL, 0, NULL) != 0)
		LOG_ERROR("Couldn't open file "+path);
	if (av_find_stream_info(pFormatCtx) < 0)
		LOG_ERROR("Couldn't find stream information.");
	Uint8 videoStream;
	bool foundVideoStream = false;
	for (Uint8 i=0; i<pFormatCtx->nb_streams; i++)
		if (pFormatCtx->streams[i]->codec->codec_type == CODEC_TYPE_VIDEO) {
			foundVideoStream = true;
			videoStream = i;
			break;
		}
	if (foundVideoStream)
		LOG_ERROR("Didn't find a video stream.");
	AVCodecContext* pCodecCtx = pFormatCtx->streams[videoStream]->codec;
	AVCodec* pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
	if (pCodec == NULL)
		LOG_ERROR("Codec not found.");
	if (pCodec->capabilities & CODEC_CAP_TRUNCATED)
		pCodecCtx->flags |= CODEC_FLAG_TRUNCATED;
	if (avcodec_open(pCodecCtx, pCodec) < 0)
		LOG_ERROR("Could not open codec.");
	AVFrame* pFrame = avcodec_alloc_frame();//must be externally private declarated?
}

bool VideoStream::get_next_frame(AVFormatContext* pFormatCtx, AVCodecContext* pCodecCtx, Uint8 videoStream, AVFrame* pFrame) {
    static AVPacket packet;
    static int      bytesRemaining=0;
    static uint8_t  *rawData;
    static bool     fFirstTime=true;
    int             bytesDecoded;
    int             frameFinished;

    // First time we're called, set packet.data to NULL to indicate it
    // doesn't have to be freed
    if(fFirstTime)
    {
        fFirstTime=false;
        packet.data=NULL;
    }

    // Decode packets until we have decoded a complete frame
    while(true)
    {
        // Work on the current packet until we have decoded all of it
        while(bytesRemaining > 0)
        {
            // Decode the next chunk of data
            bytesDecoded=avcodec_decode_video(pCodecCtx, pFrame,
                &frameFinished, rawData, bytesRemaining);

            // Was there an error?
            if(bytesDecoded < 0)
            {
                fprintf(stderr, "Error while decoding frame\n");
                return false;
            }

            bytesRemaining-=bytesDecoded;
            rawData+=bytesDecoded;

            // Did we finish the current frame? Then we can return
            if(frameFinished)
                return true;
        }

        // Read the next packet, skipping all packets that aren't for this
        // stream
        do
        {
            // Free old packet
            if(packet.data!=NULL)
                av_free_packet(&packet);

            // Read new packet
            if(av_read_packet(pFormatCtx, &packet)<0)
                goto loop_exit;
        } while(packet.stream_index!=videoStream);

        bytesRemaining=packet.size;
        rawData=packet.data;
    }

loop_exit:

    // Decode the rest of the last frame
    bytesDecoded=avcodec_decode_video(pCodecCtx, pFrame, &frameFinished, 
        rawData, bytesRemaining);

    // Free last packet
    if(packet.data!=NULL)
        av_free_packet(&packet);

    return frameFinished!=0;
}
