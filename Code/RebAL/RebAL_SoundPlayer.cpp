#include "RebAL_SoundPlayer.h"


RALSource::RALSource()
{
	loop = AL_FALSE;

	alGenSources((ALuint)1, &source);
// check for errors

alSourcef(source, AL_PITCH, 1);
alSourcef(source, AL_GAIN, 1);
alSource3f(source, AL_POSITION, 0, 0, 0);
alSource3f(source, AL_VELOCITY, 0, 0, 0);
alSourcei(source, AL_LOOPING, AL_FALSE);

ALenum error = alGetError();
alGenBuffers((ALuint)3, buffer);

}


void RALSource::SetSound()
{
	rd.SetSource("war.mp3");
	for(int i = 0; i < 3; i++)
	{
	rd.decode(buffer[i]);
	}

	/*rd.Load_Wave_File("beep.wav", buffer);*/
}

void RALSource::Update()
{

	while(1)
	{
					ALuint buff[3];
                   ALint val;
                 
                       alGetSourcei(source, AL_BUFFERS_PROCESSED, &val);
                   if(val > 0)
				   {
                 
                   // fill and requeue the empty buffer
                   alSourceUnqueueBuffers(source, val, buff);
				   for(short i = 0; i < val; i++)
				   {
				   rd.decode(buff[i]);
				   }
				  /* rd.Load_Wave_File("sine.wav", buff);*/
                   alSourceQueueBuffers(source, val, buff);
				  
                   if(alGetError() != AL_NO_ERROR) {
                       fprintf(stderr, "Error buffering :(\n");
                   }
				   }
				   
				   if(alGetError() != AL_NO_ERROR) {
                       fprintf(stderr, "Error buffering :(\n");
				   }
				   alGetSourcei(source, AL_SOURCE_STATE, &val);
                   if(val != AL_PLAYING)
                       alSourcePlay(source);
	}
}

void RALSource::Play()
{
	
	/*
	if(alGetError() != AL_NO_ERROR) {
                       fprintf(stderr, "Error loading :(\n");
	}*/
		alSourceQueueBuffers(source, 3, buffer);
	alSourcePlay(source);
	ut = std::thread(&RALSource::Update, this);

	//alSourcei(source, AL_BUFFER, buffer);


}


void RebALSS::Test()
{
	s.SetSound();
	s.Play();
}

void RebALSS::Update()
{
	s.Update();
}