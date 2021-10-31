#include "AI_StateSteal.h"

AI_StateSteal::AI_StateSteal()
{
	sBehavior = SteeringBehavior();
}

AI_StateSteal::AI_StateSteal(float _maxVelocity, float _maxSpeed, float _maxForce, float _mass)
{
	sBehavior = SteeringBehavior(_maxVelocity, _maxSpeed, _maxForce, _mass);
}

AI_StateSteal::~AI_StateSteal()
{
}

void AI_StateSteal::Enter()
{
	sBehavior.SetBehavior(BEHAVIOR::PERSUIT);
}

AI_STATE_TYPE AI_StateSteal::Update(gl::AI* _agent)
{
	if (_agent->GetSteeringBehavior().GetBehavior() != sBehavior.GetBehavior());
	_agent->GetSteeringBehavior().SetBehavior(sBehavior.GetBehavior());

	return AI_STATE_TYPE::STEAL_FLAG;

	std::cout << "Unexpected" << std::endl;
}

void AI_StateSteal::Exit()
{
	
}
