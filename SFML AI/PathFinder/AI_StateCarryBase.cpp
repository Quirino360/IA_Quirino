#include "AI_StateCarryBase.h"

AI_StateCarryBase::AI_StateCarryBase()
{
	sBehavior = SteeringBehavior();
}

AI_StateCarryBase::AI_StateCarryBase(float _maxVelocity, float _maxSpeed, float _maxForce, float _mass)
{
	sBehavior = SteeringBehavior(_maxVelocity, _maxSpeed, _maxForce, _mass);
}

AI_StateCarryBase::~AI_StateCarryBase()
{
}

void AI_StateCarryBase::Enter()
{
	sBehavior.SetBehavior(BEHAVIOR::PERSUIT);
}

//go for the falg if someone has it
AI_STATE_TYPE AI_StateCarryBase::Update(gl::AI& _agent)
{
	if (_agent.GetSteeringBehavior().GetBehavior() != sBehavior.GetBehavior());
	_agent.GetSteeringBehavior().SetBehavior(sBehavior.GetBehavior());

	return AI_STATE_TYPE::CARRY_FLAG_TO_BASE;

	_agent.SetPosition(_agent.GetPosition() + (_agent.GetSteeringBehavior().GetVelocity()));

}

void AI_StateCarryBase::Exit()
{
}
