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
AI_STATE_TYPE AI_StateCover::Update(gl::AI* _agent)
{

	if (_agent->GetSteeringBehavior().GetBehavior() != sBehavior.GetBehavior());
	_agent->GetSteeringBehavior().SetBehavior(sBehavior.GetBehavior());

	_agent->SetPosition(_agent->GetPosition() + _agent->GetSteeringBehavior().GetVelocity());

	return AI_STATE_TYPE::COVER_FLAG_CARRIER;

	std::cout << "Unexpected" << std::endl;
}

void AI_StateCover::Exit()
{
}
