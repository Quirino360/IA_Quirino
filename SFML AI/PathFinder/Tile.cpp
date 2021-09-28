#include "Tile.h"

#include "Input.h"
#include "Game.h"

#include <iostream>
#include <stdlib.h> //for the random


Tile::Tile()
{

}

Tile::~Tile()
{
}

void Tile::SetColorByType(TILE_TYPE _tileType)
{
	switch (_tileType)
	{
	case TILE_TYPE::EMPTY:
		rShape.setFillColor(sf::Color::White);
		break;
	case TILE_TYPE::WALL:
		rShape.setFillColor(sf::Color::Black);
		break;
	case TILE_TYPE::PLAYER:
		rShape.setFillColor(sf::Color::Blue);
		break;
	case TILE_TYPE::PLAYER_INSTANCE:
		rShape.setFillColor(sf::Color::Yellow);
		break;
	case TILE_TYPE::TARGET:
		rShape.setFillColor(sf::Color::Red);
		break;
	case TILE_TYPE::ROAD:
		rShape.setFillColor(sf::Color::Magenta);
		break;
	}
}

void Tile::Init(Game* _game, sf::Vector2f _size, TILE_TYPE _type)
{
	//set game pointer
	game = _game;

	//set the tileType
	tileType = _type;

	//set the rectangle shape 
	SetColorByType(tileType);
	rShape.setSize(_size);
	rShape.setOrigin({ rShape.getSize().x / 2, rShape.getSize().y / 2});
	rShape.setOutlineColor(sf::Color::Black);
	rShape.setOutlineThickness(1.0f);

	//set the weight of the tile, with a random float
	float min = 100;
	float max = 0;
	rightWeight = min + (std::rand() / (RAND_MAX / (max - min)));
	leftWeight = min + (std::rand() / (RAND_MAX / (max - min)));
}

void Tile::Update()
{


}

void Tile::ProcessEvents()
{
	
}

void Tile::Render(sf::RenderWindow* window)
{
	window->draw(rShape);
}

void Tile::Destroy()
{

}

void Tile::ChangeObjectType(TILE_TYPE _tileType)
{
	tileType = _tileType;
	SetColorByType(tileType);
}



bool Tile::IsMouseOver()
{
	//This checks if is over a tile & checks if the tile is not something already
	if (sf::Mouse::getPosition(*game->getWindow()).x > rShape.getPosition().x - rShape.getSize().x / 2 && sf::Mouse::getPosition(*game->getWindow()).x < rShape.getPosition().x + rShape.getSize().x / 2
		&& sf::Mouse::getPosition(*game->getWindow()).y > rShape.getPosition().y - rShape.getSize().y / 2 && sf::Mouse::getPosition(*game->getWindow()).y < rShape.getPosition().y + rShape.getSize().y / 2)
	{
		return true;
	}
	return false;
}
