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

	sf::CircleShape playerCircleShape;
	sf::Vector2f movement = sf::Vector2f(1.0f ,1.0f);


private:
	unsigned int ID = 0;
	sf::Shape* playerShape = nullptr;
	sf::Texture player_Texture;
	sf::Vector2f playerPosition;

	float MaxVelocity = 200;
	float velocity = 200;

public:




private:
	
	void Move();
	sf::Vector2f MultiplyVector(sf::Vector2f A, sf::Vector2f B);
};
}