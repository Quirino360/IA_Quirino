#include "Player.h"

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "DeltaTime.h";

#include "Actor.h"

#include <iostream>
#include <cmath>


sf::Clock deltaClock;

Player::Player()
{
}

void Player::Init(sf::Vector2f _position)
{
	Actor::Init(_position);
}

void Player::Update()
{
	Actor::Update();
	Move();
}

void Player::Render(sf::RenderWindow* window)
{
	Actor::Render(window);
}

void Player::Destroy()
{
	Actor::Destroy();
}

void Player::Move()
{
	float deltaTime = deltaClock.restart().asSeconds();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		velocity = sf::Vector2f(0, -1);
		position += velocity * force / mass;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		velocity = sf::Vector2f(0, 1);
		position += velocity * force / mass;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity = sf::Vector2f(-1, 0);
		position += velocity * force / mass;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity = sf::Vector2f(1, 0);
		position += velocity * force / mass;
	}
}

sf::Vector2f Player::MultiplyVector(sf::Vector2f A, sf::Vector2f B)
{
	return sf::Vector2f(A.x * B.x, A.y * B.x);
}


