#include "StatePersuit.h"

StatePersuit::StatePersuit(float _maxVelocity, float _maxSpeed, float _maxForce, float _mass)
{
	sBehavior = SteeringBehavior(_maxVelocity, _maxSpeed, _maxForce, _mass);
}

StatePersuit::~StatePersuit()
{
}

void StatePersuit::Enter()
{
	sBehavior.SetBehavior(BEHAVIOR::PERSUIT);
}

void StatePersuit::Update(sf::Vector2f _thisPostion, sf::Vector2f _targetMovement, sf::Vector2f _targetPosition)
{
	sBehavior.UpdateMovement(_thisPostion, _targetMovement, _targetPosition);
}

void StatePersuit::Exit()
{
}
