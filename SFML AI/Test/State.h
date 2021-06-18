#pragma once
#include "SteeringBehavior.h"

enum class STATES
{
	STATE_FLEE = 0,
	STATE_PATROL,
	STATE_PERSUIT,
	STATE_SEEK,
};

class State
{
public: 
	State();
	virtual ~State();

private:

public:
	virtual void Enter() = 0;
	virtual void Update(sf::Vector2f _thisPostion, sf::Vector2f _targetMovement, sf::Vector2f _targetPosition) = 0;
	virtual void Exit() = 0;

	virtual sf::Vector2f GetVelocity() = 0;
private:
};

