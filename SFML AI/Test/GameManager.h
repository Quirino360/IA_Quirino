#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Player.h"
#include "AI.h"

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

	unsigned int IDplayer = 0;
	std::vector<Player> players;

	unsigned int ID_ai = 0;
	std::vector<AI> AIs;

public:

	void InitLevel();
	void RenderManager();

	void createPlayer();
	void createPlayer(sf::Shape* shape);
	void createPlayer(sf::Vector2f position);
	void createPlayer(sf::Shape* shape, sf::Vector2f position);

	void createIA();
	void createIA(sf::Shape* shape);
	void createIA(sf::Vector2f position);
	void createIA(sf::Shape* shape, sf::Vector2f position);

	gl::Player GetPlayerByID(int id);



private:
};
}