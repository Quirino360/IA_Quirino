#include "GameManager.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

gl::GameManager::GameManager()
{
	srand(time(NULL));
}

void gl::GameManager::Init()
{
}

void gl::GameManager::Update()
{
	for (int i = 0; i < players.size(); i++)
	{
		players[i].Update();
	}
}

void gl::GameManager::Render(sf::RenderWindow* window)
{
	for (int i = 0; i < players.size(); i++)
	{
		players[i].Render(window);
	}
}

void gl::GameManager::Destroy()
{
}

void gl::GameManager::createPlayer()
{
	posX = rand() % 500 + 1;
	posY = rand() % 500 + 1;
	players.push_back(Player(sf::Vector2f(posX, posY)));
}

void gl::GameManager::createPlayer(sf::Shape* shape)
{
}

void gl::GameManager::createPlayer(sf::Vector2f position)
{
}

void gl::GameManager::createPlayer(sf::Shape* shape, sf::Vector2f position)
{
}
