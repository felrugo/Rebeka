#ifndef RALSP
#define RALSP

#include "..\RebAudio\IAudioDevice.h"
#include <AL/al.h>
#include <AL/alc.h>
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}
#include "RebFFMpeg.h"
#include <thread>


class RALSource : public SoundSource
{
	ALuint source;
	ALuint buffer[3];
	ALsizei size, freq;
ALenum format;
ALvoid *data;
ALboolean loop;
RebDecoder rd;
std::thread ut;

public:
	RALSource();
	void SetSound();
	void SetPosition();
	void Play();
	void Update();
	void Stop();
};

class RebALSS : public SoundSystem
{
	RALSource s;
public:
	void Test();
	void Update();
};



#endif