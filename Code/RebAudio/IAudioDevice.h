/*Audio interface*/
#ifndef IAUDIODEVICE_H
#define IAUDIODEVICE_H

#include <windows.h> 
#include <string>
#include <vector>

class SoundSource
{
};



class MusicPlayer
{
public:
	virtual void Init() = 0;

	virtual void Release() = 0;

	virtual void Play() = 0;

	virtual bool SetSource(std::string file) = 0;

	virtual bool SetSource(UINT ID) = 0;

	virtual void Pause() = 0;

	virtual void Stop() = 0;

	virtual void SetVolume(float volume) = 0;

	virtual bool IsPlaying() = 0;

	virtual ~MusicPlayer() {}
};


class SoundSystem
{
public:
	virtual void Test() = 0;
	virtual void Update() {}
};


class IAudioDevice
{
public:
	virtual void Init() = 0;

	virtual void Update()
	{
	}

	virtual void Release() = 0;

	virtual MusicPlayer * GetMusicPlayer() = 0;

	virtual SoundSystem * GetSoundSystem() = 0;

	virtual ~IAudioDevice()
	{
	}
};


//For AudioSystem
extern "C" {
void CreateAudioDevice(IAudioDevice ** NAD);
typedef void (*CREATEAUDIODEVICE)(IAudioDevice** NAD);

void ReleaseAudioDevice(IAudioDevice ** NAD);
typedef void (*RELEASEAUDIODEVICE)(IAudioDevice** NAD);
}
#endif