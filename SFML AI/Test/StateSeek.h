#pragma once
#include "State.h"
class StateSeek : public State
{
public:
	StateSeek(float _maxVelocity, float _maxSpeed, float _maxForce, float _mass);
	~StateSeek();

private:
	SteeringBehavior sBehavior;

public:
	virtual void Enter();
	virtual void Update(sf::Vector2f _thisPostion, sf::Vector2f _targetMovement, sf::Vector2f _targetPosition);
	virtual void Exit();

	sf::Vector2f GetVelocity() { return sBehavior.GetVelocity(); };
private:
};

