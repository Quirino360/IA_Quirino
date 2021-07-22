#pragma once
#include <SFML/Graphics.hpp>


class Game
{
public:
	Game() = default;
	~Game() = default;

	void run();

private:

	void init();
	void update();
	void processEvents();
	void render();
	void destroy();

public:
	sf::RenderWindow* getWindow() { return m_window; }

private:
	sf::RenderWindow* m_window;
	sf::CircleShape m_shape;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);;
};

