#include "AI_StateCapture.h"
#include "AI.h"

AI_StateCapture::AI_StateCapture()
{
	sBehavior = SteeringBehavior();
}

AI_StateCapture::AI_StateCapture(float _maxVelocity, float _maxSpeed, float _maxForce, float _mass)
{
	sBehavior = SteeringBehavior(_maxVelocity, _maxSpeed, _maxForce, _mass);
}

AI_StateCapture::~AI_StateCapture()
{
}

void AI_StateCapture::Enter()
{
	sBehavior.SetBehavior(BEHAVIOR::SEEK);
}

//if there is someone near you flee
AI_STATE_TYPE AI_StateCapture::Update(gl::AI* _agent)
{	
	if (_agent->GetSteeringBehavior().GetBehavior() != sBehavior.GetBehavior());
		_agent->GetSteeringBehavior().SetBehavior(sBehavior.GetBehavior());/**/

	_agent->SetPosition(_agent->GetPosition() + _agent->GetSteeringBehavior().GetVelocity());

	return AI_STATE_TYPE::CAPTURE_FLAG;

	std::cout << "Unexpected" << std::endl;
}

void AI_StateCapture::Exit()
{
}
