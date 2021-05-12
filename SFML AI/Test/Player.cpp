#include "Player.h"

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

gl::Player::Player()
{
	srand(time(NULL));

	playerCircleShape.setFillColor(sf::Color::Cyan);
	playerCircleShape.setPosition({ static_cast<float>(rand() % 100 + 1), static_cast<float>(rand() % 100 + 1) });
	playerCircleShape.setRadius(rand() % 20 + 1);
}

gl::Player::Player(sf::Shape* shape)
{
}

gl::Player::Player(sf::Vector2f position)
{
	playerCircleShape.setFillColor(sf::Color::Cyan);
	playerCircleShape.setPosition(position);
	playerCircleShape.setRadius(rand() % 20 + 1);
}

gl::Player::Player(sf::Shape* shape, sf::Vector2f position)
{
}

void gl::Player::Init()
{
}

void gl::Player::Update()
{
}

void gl::Player::Render(sf::RenderWindow* window)
{
	window->draw(playerCircleShape);
}

void gl::Player::Destroy()
{
}
