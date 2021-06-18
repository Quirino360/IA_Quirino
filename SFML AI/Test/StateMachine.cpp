#include "StateMachine.h"

StateMachine::StateMachine()
{
}

StateMachine::StateMachine(float _maxVelocity, float _maxSpeed, float _maxForce, float _mass)
{
	state = nullptr;
	stateFlee = new StateFlee(_maxVelocity, _maxSpeed, _maxForce, _mass);
	statePatrol = new StatePatrol(_maxVelocity, _maxSpeed, _maxForce, _mass);
	statePersuit = new StatePersuit(_maxVelocity, _maxSpeed, _maxForce, _mass);
	stateSeek = new StateSeek(_maxVelocity, _maxSpeed, _maxForce, _mass);

}

StateMachine::~StateMachine()
{
	if (nullptr == state)
	{
		delete state;
		state = nullptr;
	}
	if (nullptr == stateFlee)
	{
		delete stateFlee;
		stateFlee = nullptr;
	}
	if (nullptr == statePatrol)
	{
		delete statePatrol;
		statePatrol = nullptr;
	}
	if (nullptr == statePersuit)
	{
		delete statePersuit;
		statePersuit = nullptr;
	}
	if (nullptr == stateSeek)
	{
		delete stateSeek;
		stateSeek = nullptr;
	}
}

void StateMachine::Update(sf::Vector2f _thisPostion, sf::Vector2f _targetMovement, sf::Vector2f _targetPosition)
{
	if (state != nullptr)
	{
		state->Update(_thisPostion, _targetMovement, _targetPosition);
	}
}

void StateMachine::SetCurrentState(STATES _newState)
{
	if (state == nullptr)
		state = stateFlee;

	switch (_newState)
	{
	case STATES::STATE_FLEE:
		state->Exit();
		state = stateFlee;
		state->Enter();
		break;
	case STATES::STATE_PATROL:
		state->Exit();
		state = statePatrol;
		state->Enter();
		break;
	case STATES::STATE_PERSUIT:
		state->Exit();
		state = statePersuit;
		state->Enter();
		break;
	case STATES::STATE_SEEK:
		state->Exit();
		state = stateSeek;
		state->Enter();
		break;
	}
}