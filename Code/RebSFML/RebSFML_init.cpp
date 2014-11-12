#include "RebSFML.h"


void CreateAudioDevice(IAudioDevice **NAD)
{
	*NAD = new RebSFML;
}

void ReleaseAudioDevice(IAudioDevice **NAD)
{
	delete *NAD;
}

void RebSFML::Init()
{
	mp = new RebMusicPlayer;
	/*ss = new RebSoundSystem;*/
	mprun = true;
	ssrun = true;
}



	void RebSFML::Release()
	{
		if(mprun)
		delete mp;
		if(ssrun)
		delete ss;
	}

	MusicPlayer * RebSFML::GetMusicPlayer()
	{
		return mp;
	}

	SoundSystem * RebSFML::GetSoundSystem()
	{
		return ss;
	}

	RebSFML::~RebSFML()
	{
		Release();
	}

	