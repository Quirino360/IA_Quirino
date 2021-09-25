#pragma once
#include <SFML/Graphics.hpp>
#include "Actor.h"


class Player : public Actor
{
public:
	Player();
	~Player() = default;

	virtual void Init(sf::Vector2f _position = { 0,0 });
	virtual void Update();
	virtual void Render(sf::RenderWindow* window);
	virtual void Destroy();


private:
	bool hasFlag = false;
	
public:
private:
	void Move();
	sf::Vector2f MultiplyVector(sf::Vector2f A, sf::Vector2f B);
};
