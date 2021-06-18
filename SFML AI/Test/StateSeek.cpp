#include "StateSeek.h"

StateSeek::StateSeek(float _maxVelocity, float _maxSpeed, float _maxForce, float _mass)
{
	sBehavior = SteeringBehavior(_maxVelocity, _maxSpeed, _maxForce, _mass);
}

StateSeek::~StateSeek()
{
}

void StateSeek::Enter()
{
	sBehavior.SetBehavior(BEHAVIOR::SEEK);
}

void StateSeek::Update(sf::Vector2f _thisPostion, sf::Vector2f _targetMovement, sf::Vector2f _targetPosition)
{
	sBehavior.UpdateMovement(_thisPostion, _targetMovement, _targetPosition);
}

void StateSeek::Exit()
{
}
