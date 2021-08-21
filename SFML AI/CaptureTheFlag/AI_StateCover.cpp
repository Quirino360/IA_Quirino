#include "AI_StateCover.h"

AI_StateCover::AI_StateCover()
{
	sBehavior = SteeringBehavior();
}

AI_StateCover::AI_StateCover(float _maxVelocity, float _maxSpeed, float _maxForce, float _mass)
{
	sBehavior = SteeringBehavior(_maxVelocity, _maxSpeed, _maxForce, _mass);
}

AI_StateCover::~AI_StateCover()
{
}

void AI_StateCover::Enter()
{
	sBehavior.SetBehavior(BEHAVIOR::PERSUIT);
}

//go for the flag if no one has it
AI_STATE_TYPE AI_StateCover::Update(gl::AI& _agent)
{

	if (_agent.GetSteeringBehavior().GetBehavior() != sBehavior.GetBehavior());
	_agent.GetSteeringBehavior().SetBehavior(sBehavior.GetBehavior());

	std::vector<gl::AI> aux = *_agent.GetEnemies();
	_agent.GetSteeringBehavior().UpdateMovement(_agent.GetPosition(), _agent.GetVelocity(), aux[0].GetPosition());
	_agent.SetPosition(_agent.GetPosition() + _agent.GetSteeringBehavior().GetVelocity());

	

	if (_agent.hasFlag == true) //if agent has the flag-> he will carry the falg to base
	{
		return AI_STATE_TYPE::CARRY_FLAG_TO_BASE;
	}
	else if (_agent.hasFlag == false && _agent.alliesHasFlag == false && _agent.enemyHasFlag == true) //but if he doesnt has the flag and the enmy doesn't -> he will steal the flag
	{
		return AI_STATE_TYPE::STEAL_FLAG;
	}
	else if (_agent.hasFlag == false && _agent.alliesHasFlag == true && _agent.enemyHasFlag == false) //but if agent doesnt has the flag and his team has-> he will protect the carrier
	{
		return AI_STATE_TYPE::COVER_FLAG_CARRIER;
	}
	else //this means no one has the flag -> he will still chase it
	{
		return AI_STATE_TYPE::CAPTURE_FLAG;
	}

	std::cout << "Unexpected" << std::endl;
}

void AI_StateCover::Exit()
{
}