#include "stdafx.h"
#include "SoundGo.h"

SoundGo::SoundGo(std::string soundbufferfile)
	: soundbufferfile(soundbufferfile)
{
	soundbuffer.loadFromFile(soundbufferfile);
}

SoundGo::~SoundGo()
{
}

void SoundGo::SoundInBuffer()
{
	
}

void SoundGo::SetSound()
{
	sound.setBuffer(soundbuffer);
}

void SoundGo::SoundPlay()
{
	SetSound();
	sound.play();
	sound.setVolume(5.f);
}

