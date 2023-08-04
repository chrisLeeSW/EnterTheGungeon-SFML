#pragma once
class SoundGo
{
protected:
	float soundVolume = 50.f;
public:
	sf::String soundbufferfile;
	sf::SoundBuffer soundbuffer;
	sf::Sound sound;
	SoundGo(std::string soundbufferfile="");
	~SoundGo();

	void SetSound();
	void SoundInBuffer();
	void SoundPlay();
	void SoundStop() { sound.stop(); }
};

