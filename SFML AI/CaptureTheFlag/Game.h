#pragma once
#include <SFML/Graphics.hpp>

#include "GameManager.h"
#include "Player.h"
#include "AI.h"
#include "Flag.h"

#include "AI_StateMachine.h"
#include "Anim_StateMachine.h"

#include <vector>


/**
* @brief   manages the Game loop
* @bug     NA	*/
class Game
{
public:
	/**
	* @brief   runs the game loop
	* @param   NA
	* @bug     NA
	* @return  #void		*/
	void run();

	/**
	* @brief   gets the game window
	* @param   NA
	* @bug     NA
	* @return  sf::RenderWindow* game window		*/
	sf::RenderWindow* getWindow() { return m_window; }

	/**
	* @brief   default constructor
	* @param   NA
	* @bug     NA
	* @return  #void		*/
	Game() = default;

	/**
	* @brief   releases memory
	* @param   NA
	* @bug     NA
	* @return  NA		*/
	~Game() = default;
private:

	/**
	* @brief   Initialzes variables
	* @param   NA
	* @bug     NA
	* @return  #void		*/
	void init();

	/**
	* @brief   updates the game
	* @param   NA
	* @bug     NA
	* @return  #void		*/
	void update();

	/**
	* @brief   manages user events
	* @param   NA
	* @bug     NA
	* @return  #void		*/
	void processEvents();

	/**
	* @brief   renders instances in the game window
	* @param   NA
	* @bug     NA
	* @return  #void		*/
	void render();

	/**
	* @brief   releases memory
	* @param   NA
	* @bug     NA
	* @return  #void		*/
	void destroy();

	void restart();

private:

	sf::RenderWindow* m_window;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);;
	gl::GameManager gameManager;

	gl::AI_StateMachine stateMachine;
	gl::Anim_StateMachine animStateMachine;
	gl::AI AI_Entity;
	gl::Player player;

	//Capture the flag
	gl::Flag flag;
	float teamOneScore = 0;
	float teamTwoScore = 0;

	std::vector<gl::AI> TeamOne;
	std::vector<gl::AI> TeamTwo;

	sf::CircleShape TeamOnegoal;
	sf::CircleShape TeamTwogoal;


	float gameTime;
	float rounds; //this is optinal
};

