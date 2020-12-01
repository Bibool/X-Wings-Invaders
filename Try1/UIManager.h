#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Config;
class GameSprite;

namespace  sf
{
	 class Font;
	 class Text;
}

class UIManager : public sf::Drawable
{
private:
	// Used for the loops and to set the size
	const int	m_k_NumberOfTexts = 6;

	// How much score should be increased by
	const int   m_kScoreIncrease = 100;
	
	//Get the screen boundaries here to place text
	Config*		m_pScreenBoundary;
 	
 	// The Font used by the UI
	sf::Font*	m_pFont;

 	// The array of UI Text
	sf::Text*	m_pTextArray;

	// The masking UI Bar
	GameSprite* m_pUIBar;

	// Score and Wave int
	int m_score;
	int m_wave;
	int m_lives;



	void initializeStyle() const;

public:
	UIManager();
	~UIManager();
	// Overriding inherited draw method
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// Called to increment score / wave
	void addScoreUI();
	void addWaveUI();
	void minusLife();
	
	// Updates the score / wave / life
	void updateScoreNumber() const;
	void updateWaveNumber() const;
	void updateLifeNumber() const;

	// Checks if game is over
	bool checkLifeLeft() const;

	// Getters and Setters
	int  getScore() const	 { return m_score;  };
	void setScore(int score) { m_score = score; };
	int  getWave () const	 { return m_wave;	};
	void setWave (int wave)	 { m_wave = wave;   };
	int  getLives() const	 { return m_lives;  };
	void setLives(int lives) { m_lives = lives; };	
};
#endif
