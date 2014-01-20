#include "RebAudioSystem.h"


RebAudioSystem::RebAudioSystem()
{
	mDLL = LoadLibrary("RebSFML.dll");
	runing = false;
}

void RebAudioSystem::CreateAudioDevice()
{
	if (!runing)
	{
	CREATEAUDIODEVICE _CreateAudioDevice = 0;
	_CreateAudioDevice = (CREATEAUDIODEVICE)GetProcAddress(mDLL, "CreateAudioDevice");
	_CreateAudioDevice(&IAD);
	runing = true;
	}
}

void RebAudioSystem::ReleaseAudioDevice()
{
	if (runing)
	{
		RELEASEAUDIODEVICE _ReleaseAudioDevice = 0;
	_ReleaseAudioDevice = (RELEASEAUDIODEVICE)GetProcAddress(mDLL, "ReleaseAudioDevice");
	_ReleaseAudioDevice(&IAD);
	runing = false;
	}
}

IAudioDevice * RebAudioSystem::GetAudioDevice()
{
	return IAD;
}

RebAudioSystem::~RebAudioSystem()
{
	ReleaseAudioDevice();
}