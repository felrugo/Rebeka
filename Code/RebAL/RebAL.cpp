#include "RebAL.h"

void CreateAudioDevice(IAudioDevice ** iad)
{
	*iad = new RebAL;
}

void ReleaseAudioDevice(IAudioDevice ** iad)
{
	delete * iad;
}

void RebAL::Init()
{
	av_register_all();
	device = alcOpenDevice(NULL);
	context = alcCreateContext(device, NULL);
	alcMakeContextCurrent(context);

	ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };

alListener3f(AL_POSITION, 0, 0, 0);
alListener3f(AL_VELOCITY, 0, 0, 0);
alListenerfv(AL_ORIENTATION, listenerOri);

ss = new RebALSS();

}


void RebAL::Update()
{
	ss->Update();
}

void RebAL::Release()
{

}

MusicPlayer * RebAL::GetMusicPlayer()
{
	return 0;
}

SoundSystem * RebAL::GetSoundSystem()
{
	return ss;
}