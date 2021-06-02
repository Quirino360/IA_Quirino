#include "Flag.h"

gl::Flag::Flag()
{
	flagShape.setFillColor(sf::Color::Magenta);
	flagPosition = sf::Vector2f(540, 360);
	flagShape.setPosition(flagPosition);
	flagShape.setSize(sf::Vector2f(5.0f, 5.0f));
	flagShape.setOrigin(flagShape.getSize().x / 2, flagShape.getSize().y / 2);
}

gl::Flag::Flag(sf::Vector2f position)
{
	flagShape.setFillColor(sf::Color::Magenta);
	flagPosition = position;
	flagShape.setPosition(flagPosition);
	flagShape.setSize(sf::Vector2f(5.0f, 5.0f));
	flagShape.setOrigin(flagShape.getSize().x / 2, flagShape.getSize().y / 2);
}

gl::Flag::~Flag()
{
}

void gl::Flag::Init()
{
}

void gl::Flag::Update()
{
	flagShape.setPosition(flagPosition);
} 

void gl::Flag::Render(sf::RenderWindow* window)
{
	window->draw(flagShape);
}

void gl::Flag::Destroy()
{
}

void gl::Flag::setFlagPosition(sf::Vector2f position)
{
	flagPosition = position;
}
