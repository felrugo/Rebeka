#include "RebSFML.h"


void RebMusicPlayer::Init()
{
	playlist.clear();
	musicrun = true;
}

void RebMusicPlayer::Release()
{
	if(musicrun)
	{
	playlist.clear();
	musicrun = false;
	}
}

RebMusicPlayer::~RebMusicPlayer()
{
	Release();
}

void RebMusicPlayer::Play()
{
	music.play();
}

bool RebMusicPlayer::SetSource(std::string file)
{
bool ret =	music.openFromFile(file);
return ret;
}

bool RebMusicPlayer::SetSource(UINT ID)
{
	if(playlist.size() <= ID)
	{
		return false;
	}
	bool ret =	music.openFromFile(playlist[ID]);
return ret;
}

void RebMusicPlayer::Pause()
{
	music.pause();
}

void RebMusicPlayer::Stop()
{
	music.stop();
}

bool RebMusicPlayer::IsPlaying()
{
	if(music.getStatus() == sf::Music::Playing)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void RebMusicPlayer::SetVolume(float volume)
{
	music.setVolume(volume);
}