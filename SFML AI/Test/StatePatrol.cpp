#include "StatePatrol.h"

StatePatrol::StatePatrol(float _maxVelocity, float _maxSpeed, float _maxForce, float _mass)
{
	sBehavior = SteeringBehavior(_maxVelocity, _maxSpeed, _maxForce, _mass);
}

StatePatrol::~StatePatrol()
{
}

void StatePatrol::Enter()
{
	sBehavior.SetBehavior(BEHAVIOR::PATH_FOLLOWING);
}

void StatePatrol::Update(sf::Vector2f _thisPostion, sf::Vector2f _targetMovement, sf::Vector2f _targetPosition)
{
	sBehavior.UpdateMovement(_thisPostion, _targetMovement, _targetPosition);
}

void StatePatrol::Exit()
{
	
}
