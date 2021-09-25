#include "ActorManager.h"

#include "Player.h"
#include "AI.h"
#include "Flag.h"

void ActorManager::Init(sf::Vector2f _position)
{
}

void ActorManager::Update()
{
}

void ActorManager::Render(sf::RenderWindow* window)
{
}

void ActorManager::Destroy()
{
}

void ActorManager::CreateActor(ACTOR_TYPE _actorType, sf::Vector2f _position)
{
	switch (_actorType)
	{
	case ACTOR_TYPE::ACTOR:
		actors.push_back(new Actor());
		actors[actors.size() - 1]->Init(_position);
		break;
	case ACTOR_TYPE::PLAYER:
		actors.push_back(new Player());
		actors[actors.size() - 1]->Init(_position);
		break;
	case ACTOR_TYPE::AI:
		actors.push_back(new AI());
		actors[actors.size() - 1]->Init(_position);
		break;
	case ACTOR_TYPE::FLAG:
		actors.push_back(new Flag());
		actors[actors.size() - 1]->Init(_position);
		break;
	}
}

Actor* ActorManager::GetActorByID(unsigned int _ID)
{
	for (Actor* _actor : actors)
	{
		if (_actor->GetID() == _ID)
			return _actor;
	}
	return nullptr;
}

void ActorManager::DeleteActorByID(unsigned int _ID)
{
	for (Actor* _actor : actors)
	{
		if (_actor->GetID() == _ID)
		{
			_actor->Destroy();
			delete _actor;
			_actor = nullptr;
			//delete it from list

		}
	}
}

std::vector<Actor*> ActorManager::GetActorsByType(ACTOR_TYPE _actorType)
{
	std::vector<Actor*> actorsAux;
	for (Actor* _actor : actors)
	{
		if (_actor->GetActorType() == _actorType)
			actorsAux.push_back(_actor);
	}
	return actorsAux;
}

void ActorManager::DeleteActorsByType(ACTOR_TYPE _actorType)
{
	for (Actor* _actor : actors)
	{
		if (_actor->GetActorType() == _actorType)
			DeleteActorByID(_actor->GetID());
	}
}

void ActorManager::DeleteAllActors()
{
	for (Actor* _actor : actors)
	{
		_actor->Destroy();
		delete _actor;
		_actor = nullptr;
	}
	//delete the list
}
