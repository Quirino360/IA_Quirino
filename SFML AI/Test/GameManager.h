#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Player.h"

namespace gl {
class GameManager
{
public:
	GameManager();
	~GameManager() = default;

	void Init();
	void Update();
	void Render(sf::RenderWindow* window);
	void Destroy();

private:
	float initialPosX = 0;
	float initialPosY = 0;

	unsigned int IDplayerCount = 0;
	std::vector<Player> players;

public:
	void createPlayer();
	void createPlayer(sf::Shape* shape);
	void createPlayer(sf::Vector2f position);
	void createPlayer(sf::Shape* shape, sf::Vector2f position);

	gl::Player GetPlayerByID(int id);



private:
};
}