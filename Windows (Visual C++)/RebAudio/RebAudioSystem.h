#ifndef REBAUDIOSYSTEM_H
#define REBAUDIOSYSTEM_H

#include "IAudioDevice.h"



class RebAudioSystem
{
	IAudioDevice * IAD;
	HMODULE mDLL;
	  bool runing;
public:

	RebAudioSystem();

	void CreateAudioDevice();

	void ReleaseAudioDevice();

	IAudioDevice * GetAudioDevice();

	~RebAudioSystem();
};

#endif