#pragma once
#include <SFML/Graphics.hpp>
#include "CTexture.h"

namespace gl {
class Player
{
public:
	Player();
	Player(sf::Shape* shape);
	Player(sf::Vector2f position);
	Player(sf::Shape* shape, sf::Vector2f position);
	~Player() = default;

	void Init();
	void Update();
	void Render(sf::RenderWindow * window);
	void Destroy();

private:
	unsigned int ID = 0;
	sf::Shape* playerShape = nullptr;
	sf::CircleShape playerCircleShape;
	sf::Texture player_Texture;
	sf::Vector2f playerPosition;

public:

private:
};
}