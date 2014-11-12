#ifndef REBAL_H
#define REBAL_H

#include "..\RebAudio\IAudioDevice.h"
#include <AL/al.h>
#include <AL/alc.h>
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

#include "RebAL_SoundPlayer.h"

class RebAL : public IAudioDevice
{
ALCdevice *device;
ALCcontext *context;

SoundSystem * ss;

public:
	void Init();

	void Update();

	void Release();

	MusicPlayer * GetMusicPlayer();

	SoundSystem * GetSoundSystem();

	~RebAL()
	{
	}
};



#endif