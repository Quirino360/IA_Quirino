#pragma once
#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "Player.h"

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

};

