/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include "SFML/Audio.hpp"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 1200U, 900U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	loadContent(); // load font 
	//setupSprite(); // load texture
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	if (gamemode == splashscreen)
	{
		m_music.play();
		m_music.setLoop(true);
		m_music.setVolume(70);
		m_music.setRelativeToListener(true);
		count++;
		m_message.setString("Created, Produced and Directed by \n Obrigado Studios");
		m_message.setCharacterSize(30U);
		m_message.setOrigin(m_message.getGlobalBounds().width / 2, m_message.getGlobalBounds().height / 2);
		m_message.setLineSpacing(5);
		m_message.setPosition(600.0f, 450.0f);
		m_message.setFillColor(sf::Color::White);
		m_message.setFont(m_gameFont);
		std::cout << std::to_string(count) + "\n";
		if (count == 180)
		{ 
			gamemode = mainmenu;
		}
	}
	if (gamemode == mainmenu)
	{
		
		sf::String m_menuButtonText[] = { "Press Enter to Play", "Instructions", "Press Esc to Quit" };
		for (size_t i = 0; i < 2; i++)
		{
			m_menuMessage[i].setFont(m_gameFont);
			m_menuMessage[i].setString(m_menuButtonText[i]);
			m_menuMessage[i].setCharacterSize(30U);
			m_menuMessage[i].setPosition(600.0f - m_menuMessage[i].getGlobalBounds().width / 2, 200.0f * (i + 1));
			m_menuMessage[i].setFillColor(sf::Color::White);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
		{
			gamemode = instructions;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			gamemode = gameplay;
		}
	}
	if (gamemode == instructions)
	{
		m_message.setString("Use the Arrow Keys to move\nspacebar to shoot the enemies\nPress Backspace to return to main menu\nS U R V I V E !");
		m_message.setCharacterSize(30U);
		m_message.setPosition(600.0f - m_message.getGlobalBounds().width / 2, 450.0f - m_message.getGlobalBounds().height / 2);//sets the messaqge on the middle of the screen
		m_message.setFillColor(sf::Color::White);
		m_message.setLineSpacing(1.0f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace))
		{
			gamemode = mainmenu;
		}
	}
	if (gamemode == gameplay)
	{
		m_message.setString("Insert gameplay here \n Press enter to end game");
		m_message.setCharacterSize(60U);
		m_message.setPosition(600.0f - m_message.getGlobalBounds().width / 2, 450.0f - m_message.getGlobalBounds().height / 2);
		m_message.setFillColor(sf::Color::White);
		m_message.setFont(m_gameFont);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			gamemode = endscreen;
		}
	}
	if (gamemode == endscreen) 
	{
		m_message.setString("You Died magically\n Press space to Try Again!");
		m_message.setCharacterSize(30U);
		m_message.setPosition(600.0f - m_message.getGlobalBounds().width / 2, 450.0f - m_message.getGlobalBounds().height / 2);//sets the messaqge on the middle of the screen
		m_message.setFillColor(sf::Color::White);
		m_message.setLineSpacing(3.0f);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			gamemode = gameplay;
		}
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	if (gamemode == splashscreen)
	{
		m_window.clear(sf::Color::Green);
		m_window.draw(m_message);
	}
	if (gamemode == mainmenu)
	{
		m_window.clear(sf::Color(40, 116, 237));
		for (size_t i = 0; i < 3; i++)
		{
			m_window.draw(m_menuMessage[i]);
		}
	}
	if (gamemode == instructions)
	{
		m_window.clear(sf::Color(40, 187, 197));
		m_window.draw(m_message);
	}
	if (gamemode == gameplay)
	{
		m_window.clear(sf::Color(157, 132, 184));
		m_window.draw(m_message);
	}
	if (gamemode == endscreen)
	{
		m_window.clear(sf::Color::Red);
		m_window.draw(m_message);
	}
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::loadContent()
{
	if (!m_gameFont.loadFromFile("ASSETS\\FONTS\\Copperplate Gothic Bold Regular.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_message.setFont(m_gameFont);

	if (!m_music.openFromFile("ASSETS\\AUDIO\\Silhouette.ogg"))
	{
		std::cout << "error loading music file, opps...";
	}
}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
//void Game::setupSprite()
//{
//	if (!m_gameFont.loadFromFile("ASSETS\\IMAGES\\SFML-LOGO.png"))
//	{
//		// simple error message if previous call fails
//		std::cout << "problem loading logo" << std::endl;
//	}
//	m_logoSprite.setTexture(m_logoTexture);
//	m_logoSprite.setPosition(300.0f, 180.0f);
//}
