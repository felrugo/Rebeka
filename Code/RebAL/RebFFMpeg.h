#ifndef REBFFMPEG
#define REBFFMPEG

#include <AL/al.h>
#include <AL/alc.h>
#include <AL\alext.h>
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libswresample\swresample.h>
}
#include <string>
#include <Windows.h>
#include <iostream>

class RebDecoder
{

	AVFormatContext* container;
	AVCodecContext* codec_context;
	AVCodec* codec;
	int stream_id;
	AVPacket packet;
	SwrContext* swrContext;
	uint8_t** destBuffer;
	int destBufferLinesize;

public:
	void * testdata;
	RebDecoder();
	void Load_Wave_File(char *fname, unsigned int buff);
	void SetSource(std::string file);
	void decode(unsigned int buff, ALuint frequency = 44100, ALenum format = AL_FORMAT_STEREO16);
	~RebDecoder();
};


#endif