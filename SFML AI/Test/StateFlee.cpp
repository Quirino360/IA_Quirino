#include "StateFlee.h"

StateFlee::StateFlee(float _maxVelocity, float _maxSpeed, float _maxForce, float _mass)
{
	sBehavior = SteeringBehavior(_maxVelocity, _maxSpeed, _maxForce, _mass);
}

StateFlee::~StateFlee()
{
}

void StateFlee::Enter()
{
	sBehavior.SetBehavior(BEHAVIOR::FLEE);
}

void StateFlee::Update(sf::Vector2f _thisPostion, sf::Vector2f _targetMovement, sf::Vector2f _targetPosition)
{
	sBehavior.UpdateMovement(_thisPostion, _targetMovement, _targetPosition);
}

void StateFlee::Exit()
{
}
