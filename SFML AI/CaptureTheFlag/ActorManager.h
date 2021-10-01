#pragma once
#include <SFML/Graphics.hpp>

#include "Actor.h"

#include <vector>


class ActorManager
{
public:
	ActorManager() = default;
	~ActorManager() = default;

	void Init(sf::Vector2f _position = { 0,0 });
	void Update();
	void Render(sf::RenderWindow* window);
	void Destroy();

private:
	std::vector<Actor*> actors;
	unsigned int ID_Count = 0;

public:
	void CreateActor(ACTOR_TYPE _actorType = ACTOR_TYPE::AI, sf::Vector2f _position = {0, 0});

	Actor* GetActorByID(unsigned int _ID);
	void DeleteActorByID(unsigned int _ID);

	std::vector<Actor*> GetActorsByType(ACTOR_TYPE _actorType);
	void DeleteActorsByType(ACTOR_TYPE _actorType);

	std::vector<Actor*> GetAllActors() { return actors; };
	void DeleteAllActors();

private:
};

