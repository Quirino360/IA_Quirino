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
	initialPosX = rand() % 500 + 1;
	initialPosY = rand() % 500 + 1;
	players.push_back(Player(sf::Vector2f(initialPosX, initialPosY)));
}

void gl::GameManager::createPlayer(sf::Shape* shape)
{
}

void gl::GameManager::createPlayer(sf::Vector2f position)
{
	players.push_back(Player(position));
}

void gl::GameManager::createPlayer(sf::Shape* shape, sf::Vector2f position)
{
}

gl::Player gl::GameManager::GetPlayerByID(int id)
{
	if (players.size() > id)
		return players[id];

	return Player();
}

