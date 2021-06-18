#pragma once
#include "State.h"
#include "StateFlee.h"
#include "StatePatrol.h"
#include "StatePersuit.h"
#include "StateSeek.h"

class StateMachine
{
public:
	StateMachine();
	StateMachine(float _maxVelocity, float _maxSpeed, float _maxForce, float _mass);
	~StateMachine();

	void Update(sf::Vector2f _thisPostion, sf::Vector2f _targetMovement, sf::Vector2f _targetPosition);

private:
	State* state;

	StateFlee* stateFlee;
	StatePatrol* statePatrol;
	StatePersuit* statePersuit;
	StateSeek* stateSeek;

public:
	void SetCurrentState(STATES _newState);
	State* GetCurentState() { return state; };
private:
};

