#pragma once
#include <SFML/Graphics.hpp>
#include "Actor.h"
#include "SteeringBehavior.h"

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
	Actor* target = nullptr;
	bool hasFlag = false;
	
	// Steering Behavior
	SteeringBehavior sBehavior;
public:
private:
	void Move();

};
