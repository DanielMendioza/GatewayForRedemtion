/// <summary>
/// author Pete Lowe May 2019
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void loadContent();
	//void setupSprite();
	sf::Text m_menuMessage[3];
	sf::Text m_menuButtonText[3];
	int gamemode = splashscreen;
	sf::Music m_music;
	sf::SoundBuffer m_musicbuffer;

	enum screen {
		splashscreen,
		mainmenu,
		instructions,
		gameplay,
		endscreen
	};
	int count = 0;
	sf::Text m_message;
	sf::Font m_gameFont;

	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

