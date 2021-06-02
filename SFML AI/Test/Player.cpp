#include "Player.h"

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "DeltaTime.h";

#include <cmath>

sf::Clock deltaClock;
gl::Player::Player()
{
	srand(time(NULL));

	playerCircleShape.setFillColor(sf::Color::Magenta);
	playerPosition = sf::Vector2f(540, 360);
	playerCircleShape.setPosition(playerPosition);
	playerCircleShape.setRadius(10);
	playerCircleShape.setOrigin(playerCircleShape.getRadius() / 2, playerCircleShape.getRadius() / 2);
}

gl::Player::Player(sf::Shape* shape)
{
}

gl::Player::Player(sf::Vector2f position)
{
	playerCircleShape.setFillColor(sf::Color::Magenta);
	playerPosition = position;
	playerCircleShape.setPosition(playerPosition);
	playerCircleShape.setRadius(10);
	playerCircleShape.setOrigin(playerCircleShape.getRadius() / 2, playerCircleShape.getRadius() / 2);
}

gl::Player::Player(sf::Shape* shape, sf::Vector2f position)
{
}

void gl::Player::Init()
{
}

void gl::Player::Update()
{
	Move();
}

void gl::Player::Render(sf::RenderWindow* window)
{
	window->draw(playerCircleShape);
}

void gl::Player::Destroy()
{
}

void gl::Player::Move()
{
	float deltaTime = deltaClock.restart().asSeconds();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		movement = sf::Vector2f(0, -1);
		playerCircleShape.move(movement * velocity * deltaTime);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		movement = sf::Vector2f(0, 1);
		playerCircleShape.move(movement * velocity * deltaTime);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		movement = sf::Vector2f(-1, 0);
		playerCircleShape.move(movement * velocity * deltaTime);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		movement = sf::Vector2f(1, 0);
		playerCircleShape.move(movement * velocity * deltaTime);
	}
}

sf::Vector2f gl::Player::MultiplyVector(sf::Vector2f A, sf::Vector2f B)
{
	return sf::Vector2f(A.x * B.x, A.y * B.x);
}


