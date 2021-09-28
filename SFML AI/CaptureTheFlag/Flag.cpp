#include "Flag.h"

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "DeltaTime.h";
#include <iostream>


Flag::Flag()
{

}

Flag::~Flag()
{
}

void Flag::Init(sf::Vector2f _position)
{
	Actor::Init(_position);
}

void Flag::Update()
{
	Actor::Update();
}

void Flag::Render(sf::RenderWindow* window)
{
	Actor::Render(window);
}

void Flag::Destroy()
{
	Actor::Destroy();
}

bool Flag::DetectIfAITouch(sf::CircleShape _detect, bool _ignore)
{
	if (DistanceBetweenVectors(_detect.getPosition(), cShape.getPosition()) - _detect.getRadius() <= _detect.getRadius() && !_ignore)
		return true;
	return false;
}

void Flag::ResetFlag()
{
	isOnPlayer = false;
	position = sf::Vector2f(rand() % 1060 + 1, rand() % 700 + 1);
	cShape.setPosition(position);
}

float Flag::DistanceBetweenVectors(sf::Vector2f A, sf::Vector2f B)
{
	float a = A.x - B.x;
	float b = A.y - B.y;
	return std::sqrtf(std::powf(a, 2) + std::powf(b, 2));
}
