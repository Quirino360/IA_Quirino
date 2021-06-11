#include "Flag.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "DeltaTime.h";

namespace gl
{
	Flag::Flag()
	{
		srand(time(NULL));
		flagShape.setFillColor(sf::Color::White);
		flagPosition = sf::Vector2f(rand() % 1060 + 1, rand() % 700 + 1);
		flagShape.setPosition(flagPosition);
		flagShape.setRadius(10);
		flagShape.setOrigin(flagShape.getRadius() / 2, flagShape.getRadius() / 2);
	}

	Flag::Flag(sf::Vector2f position)
	{
		flagShape.setFillColor(sf::Color::Magenta);
		flagPosition = position;
		flagShape.setPosition(flagPosition);
		flagShape.setRadius(10);
		flagShape.setOrigin(flagShape.getRadius() / 2, flagShape.getRadius() / 2);
	}

	Flag::~Flag()
	{
	}

	void Flag::Init()
	{
	}

	void Flag::Update()
	{
		flagShape.setPosition(flagPosition);
	}

	void Flag::Render(sf::RenderWindow* window)
	{
		window->draw(flagShape);
	}

	void Flag::Destroy()
	{
	}

	bool Flag::DetectIfAITouch(sf::CircleShape _detect, bool _ignore)
	{
		if (DistanceBetweenVectors(_detect.getPosition(), flagShape.getPosition()) - _detect.getRadius() <= _detect.getRadius() && !_ignore)
			return true;
		return false;
	}

	void Flag::ResetFlag()
	{
		isOnPlayer = false;
		flagPosition = sf::Vector2f(rand() % 1060 + 1, rand() % 700 + 1);
		flagShape.setPosition(flagPosition);
	}

	void Flag::setFlagPosition(sf::Vector2f position)
	{
		flagPosition = position;
	}

	float Flag::DistanceBetweenVectors(sf::Vector2f A, sf::Vector2f B)
	{
		float a = A.x - B.x;
		float b = A.y - B.y;
		return std::sqrtf(std::powf(a, 2) + std::powf(b, 2));
	}
}