#include "RebSFML.h"

void RebSoundSource::Init()
{
	sound.setBuffer(buffer);
}

void RebSoundSource::Release()
	{

	}

RebSoundSource::~RebSoundSource()
{
	Release();
}

void RebSoundSource::LoadSound(std::string file)
{
	buffer.loadFromFile(file);
}

void RebSoundSource::SetLoop(bool loop)
{
	sound.setLoop(loop);
}

void RebSoundSource::Play()
{
	sound.play();
}

void RebSoundSource::Pause()
{
	sound.pause();
}

void RebSoundSource::Stop()
{
	sound.stop();
}