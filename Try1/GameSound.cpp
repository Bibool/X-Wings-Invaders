#include "GameSound.h"
#include "Helpers.h"

GameSound::GameSound(const char* soundTrack)
{
	bool loaded = m_soundBuffer.loadFromFile(soundTrack);
	ASSERT_CHECK(loaded);
	setBuffer(m_soundBuffer);
}

GameSound::~GameSound()
{
	
}

