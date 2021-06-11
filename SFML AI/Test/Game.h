#pragma once
#include <SFML/Graphics.hpp>

#include "GameManager.h"
#include "Player.h"
#include "AI.h"
#include "Flag.h"

#include <vector>

class Game
{
public:
	void run();

	sf::RenderWindow* getWindow() { return m_window; }

	Game() = default;
	~Game() = default;
private:

	void init();
	void update();
	void processEvents();
	void render();
	void destroy();

private:

	sf::RenderWindow* m_window;

	sf::Time timePerFrame = sf::seconds(1.f / 60.f);;

	gl::GameManager gameManager;
	//gl::AI AI_Entity;
	//gl::Player player;

	gl::Flag flag;


	//Capture the flag
	std::vector<gl::AI> TeamOne;
	std::vector<gl::AI> TeamTwo;

	bool teamOneHasTheFlag = false;
	bool teamTwoHasTheFlag = false;

	float teamOneScore;
	float teamTwoScore;

	float gameTime;
	float rounds; //this is optinal
};

