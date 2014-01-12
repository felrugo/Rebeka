#ifndef REBSFML_H
#define REBSFML_H

#include "..\RebAudio\IAudioDevice.h"
#include "SFML\Audio.hpp"
#include "..\Reb3D\Reb3D.h"


class RebMusicPlayer : public MusicPlayer
{
	std::vector<std::string> playlist;

	sf::Music music;

	bool musicrun;

public:

	void Init();

	void Release();

	void Play();

	bool SetSource(std::string file);

	bool SetSource(UINT ID);

	void Pause();

	void Stop();

	void SetVolume(float volume);

	bool IsPlaying();

	~RebMusicPlayer();
};


class RebSoundListener : public SoundListener
{
	sf::Listener listener;

public:

	
	
	void SetPos(RebVector pos);

	void SetOrientation(RebVector ori);

};

class RebSoundSource : public SoundSource
{
	sf::SoundBuffer buffer;

	sf::Sound sound;

public:

	void Init();

	void Release();

	void LoadSound(std::string file);

	void SetLoop(bool loop);

	void Play();

	void Pause();

	void Stop();

	~RebSoundSource();
};

class RebSoundSystem : public SoundSystem
{



public:
	void Init();

	void Release();

	~RebSoundSystem();
};

class RebSFML : public IAudioDevice
{

	MusicPlayer * mp;

	SoundSystem * ss;

	bool mprun, ssrun;

public:

	void Init();

	void Release();

	MusicPlayer * GetMusicPlayer();

	SoundSystem * GetSoundSystem();

	~RebSFML();

};




#endif