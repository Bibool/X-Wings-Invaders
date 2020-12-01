#ifndef GAMESTATES_H
#define GAMESTATES_H

// A very simple class that holds the game states of the game
// It self initializes to menu and holds a public variable
// for ease of access

class GameStates
{
public:
	enum class States { Menu = 0, Playing, Paused, Intermission, GameOver } m_eStates;
	GameStates()
		: m_eStates(States::Menu)
	{
		
	}
};
#endif
