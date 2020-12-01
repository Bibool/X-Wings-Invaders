#include "GameSound.h"
#include "Helpers.h"
#include "MusicManager.h"
#include "RandomGenerator.h"



MusicManager::MusicManager()
	: m_pRandomGenerator(nullptr)
{
	// Needed to use the MTE Random number generator
	m_pRandomGenerator = new RandomGenerator();
	
	// Initializes them into the array
	// Then set the Menu music to play
	m_pSoundHolder[0]  = new GameSound("Assets/Audio/MenuMusic.wav"		   ); // Main Menu
	m_pSoundHolder[1]  = new GameSound("Assets/Audio/BackgroundMusic.wav"  ); // BGM
	m_pSoundHolder[2]  = new GameSound("Assets/Audio/MenuMusic.wav"	       ); // Death music here
	m_pSoundHolder[3]  = new GameSound("Assets/Audio/ShotEffect.wav"	   ); // Player Shoot effect
	m_pSoundHolder[4]  = new GameSound("Assets/Audio/Explosion.wav"		   ); // Explosion effects
	m_pSoundHolder[5]  = new GameSound("Assets/Audio/Explosion1.wav"	   );
	m_pSoundHolder[6]  = new GameSound("Assets/Audio/Explosion2.wav"	   );
	m_pSoundHolder[7]  = new GameSound("Assets/Audio/Explosion3.wav"	   );
	m_pSoundHolder[8]  = new GameSound("Assets/Audio/ArcadeModeEnabled.wav"); // Audio feedback when enabling alt mode
	m_pSoundHolder[9]  = new GameSound("Assets/Audio/EnemyShotEffect.wav"  ); // Enemy Shoot effect
	m_pSoundHolder[10] = new GameSound("Assets/Audio/PlayerHit.wav"		   ); // Player taking damage
	m_pSoundHolder[11] = new GameSound("Assets/Audio/GameOver.wav"		   ); // Player dying

	// Initializes the game tracks to loop
	m_pSoundHolder[1]->setLoop(true);
	m_pSoundHolder[0]->setLoop(true);
	
	// Sets the menu music to autoplay
	m_pSoundHolder[0]->play();
	
	m_isPlayingSound = false;
	CONSOLE_OUT "Music Manager constructor ran. \n";
}


void MusicManager::playRandomExplosion()
{
	m_pSoundHolder[m_pRandomGenerator->randomInt(m_kExplosionInArrayStart, m_kExplosionInArrayEnd)]->play();
}

void MusicManager::playRandomHitEffect()
{
	m_pSoundHolder[10]->play();
}

MusicManager::~MusicManager()
{
	// Delete the pointers
	safeDelete(m_pRandomGenerator);
	safeDelete(m_pSoundHolder[0]);
	safeDelete(m_pSoundHolder[1]);
	safeDelete(m_pSoundHolder[2]);
	safeDelete(m_pSoundHolder[3]);
	safeDelete(m_pSoundHolder[4]);
	safeDelete(m_pSoundHolder[5]);
	safeDelete(m_pSoundHolder[6]);
	safeDelete(m_pSoundHolder[7]);
	safeDelete(m_pSoundHolder[8]);
	safeDelete(m_pSoundHolder[9]);
	safeDelete(m_pSoundHolder[10]);
	safeDelete(m_pSoundHolder[11]);
}