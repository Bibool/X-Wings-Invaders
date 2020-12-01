#ifndef MUSICMANAGER_H
#define MUSICMANAGER_H

class GameSound;
class RandomGenerator;
////////////////////////////////////
// A simple class that manages sound
// Provides an array to be used by
// the Game manager.
////////////////////////////////////
class MusicManager
{
private:
	// Feeds into array calculations
	static const int m_kArraySize			  = 12;
	const int		 m_kExplosionInArrayStart = 4;
	const int		 m_kExplosionInArrayEnd	  = 7;
	// Used to play sound once
	bool			 m_isPlayingSound;

	// Read from config file
	RandomGenerator* m_pRandomGenerator;

public:
	MusicManager();
	~MusicManager();

	// The array of sounds
	GameSound*		 m_pSoundHolder[m_kArraySize];

	// Plays a random explosion effect
	void playRandomExplosion();

	// Plays a random hit effect
	void playRandomHitEffect();

	bool getIsPlayingSound() const				{ return m_isPlayingSound; };
	void setIsPlayingSound(bool isPlayingSound) { m_isPlayingSound = isPlayingSound; };
};
#endif