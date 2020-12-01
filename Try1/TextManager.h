#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Clock.hpp>


class Config;
class GameSprite;

////////////////////////////////////
// A simple class that manages text
// Provides an array to be used by
// the Game manager.
////////////////////////////////////
class TextManager : public sf::Drawable
{
private:
	const int	k_numberOfTexts = 7;
	const int	k_numberOfFonts = 3;

	// Fade Effect timer values
	// Picture has to fade in faster than text
	const float m_kFadeInTimer = 0.05f;
	const float m_kImageFadeTimer = 0.025f;

	// RGBA values
	int		    m_alpha;
	int			m_fadeAlpha;
	int			m_red;
	int			m_blue;
	int			m_green;

	// Reads screen settings
	Config*		m_pScreenBoundary;

	// Holds the fonts
	sf::Font*   m_pFontArray;

	// Clocks used in timings
	sf::Clock   m_clock;
	sf::Color   m_colorFade;
	sf::Color	m_blackFade;

	// Increases alpha channels over time
	void transitionEffect();


public:
	TextManager();
	~TextManager();

	sf::Text* m_pTextArray;
	GameSprite* m_pBackgroundFade;

	// Derived draw update
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	// Logic
	void update();

	// Effect played between waves
	void intermissionEffect();
	// Resets it
	void resetIntermissionEffect();

};
#endif
