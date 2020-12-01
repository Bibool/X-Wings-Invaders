#ifndef FRONTENDINPUT_H
#define FRONTENDINPUT_H

namespace sf
{
	class Keyboard;
}

class FrontEndInput
{
private:
	sf::Keyboard* m_pKeyboard;
	bool m_isEnterPressed;
	bool m_isEnterReleased;
	bool m_isEscapePressed;
	bool m_isEscapeReleased;
	bool m_isTabPressed;
	bool m_isTabReleased;
	bool m_isVPressed;

public:
	FrontEndInput();
	~FrontEndInput();
	void getInput();
	bool getKeyEnterPressed()   const { return m_isEnterPressed;  };
	bool getKeyEnterReleased()  const { return m_isEnterReleased; };
	bool getKeyEscapePressed()  const { return m_isEscapePressed; };
	bool getKeyEscapeReleased() const { return m_isEscapeReleased;};
	bool getKeyTabPressed()		const { return m_isTabPressed;    };
	bool getKeyTabReleased()	const { return m_isTabReleased;   };
	bool getKeyVPressed()		const { return m_isVPressed;	  };
};

#endif