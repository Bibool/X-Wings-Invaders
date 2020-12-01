#ifndef GAMESOUND_H
#define GAMESOUND_H

#include "SFML/Audio/SoundBuffer.hpp"
#include "SFML/Audio/Sound.hpp"

class GameSound : public sf::Sound
{
private:
	sf::SoundBuffer m_soundBuffer;
	
public:
	GameSound(const char* soundTrack);
	~GameSound();
};

#endif