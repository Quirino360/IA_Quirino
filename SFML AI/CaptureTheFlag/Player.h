#pragma once
#include <SFML/Graphics.hpp>
#include "Actor.h"
#include "SteeringBehavior.h"

enum class PLAYER_STATE_TYPE;

class Player : public Actor
{
public:
	Player();
	~Player() = default;

	virtual void Init(sf::Vector2f _position = { 0,0 }, bool setTexture = true);
	virtual void Update();
	virtual void Render(sf::RenderWindow* window);
	virtual void Destroy();

	PLAYER_STATE_TYPE* playerState;

private:
	Actor* target = nullptr;
	bool hasFlag = false;
	
	// Steering Behavior
	SteeringBehavior sBehavior;
public:
	SteeringBehavior& GetSteeringBehavior() { return sBehavior; };


private:
	void Move();

};
