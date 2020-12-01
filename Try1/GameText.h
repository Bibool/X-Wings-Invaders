#ifndef GAMETEXT_H
#define GAMETEXT_H

#include "SFML/Graphics/Text.hpp"

/////////////////////////////////
// Simple class that handles both
// Fonts and text
/////////////////////////////////
class GameText : public sf::Text
{
private:
	sf::Font m_font;
	int m_alpha;
	int m_colorR;
	int m_colorG;
	int m_colorB;
	
	float m_multiplier;
	
	// Booleans required to as checks for the glow effect to revert
	bool m_hasReachedAlpha0;
	bool m_hasReachedAlpha255;
	bool m_hasReachedR0;
	bool m_hasReachedR255;
	bool m_hasReachedG0;
	bool m_hasReachedG255;
	bool m_hasReachedB0;
	bool m_hasReachedB255;
	
public:
	GameText(const char* fontName);
	
	// An effect that makes the text glows
	void glowEffect(float deltaTime);
	void glowEffect(sf::Text &text);
	void glowRed();
	void glowBlue();
	void glowGreen();
	void glowRGB();
};
#endif