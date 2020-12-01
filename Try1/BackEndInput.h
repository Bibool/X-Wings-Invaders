#ifndef BACKENDINPUT_H
#define BACKENDINPUT_H

//Forward class declaration for the pointers
namespace sf
{
	class Keyboard;
}

class GameStates;

class BackEndInput
{
private:
	sf::Keyboard* m_pKeyboard;

	bool m_isKeyLeftPressed		: 1;
	bool m_isKeyLeftReleased	: 1;
	bool m_isKeyRightPressed	: 1;
	bool m_isKeyRightReleased   : 1;
	bool m_isKeyFirePressed		: 1;
	bool m_isKeyFireReleased	: 1;

public:
	BackEndInput();
	~BackEndInput();
	
	//Reads current input
	void getInput();
	
	//Getters to be accessed by players
	bool getKeyFirePressed()  const { return m_isKeyFirePressed;  };
	bool getKeyFireReleased() const { return m_isKeyFireReleased; };
	bool getKeyLeftPressed()  const { return m_isKeyLeftPressed;  };
	bool getKeyLeftReleased() const { return m_isKeyLeftReleased; };
	bool getKeyRightPressed() const { return m_isKeyRightPressed; };
	bool getKeyRightReleased()const { return m_isKeyRightReleased;};
};
#endif