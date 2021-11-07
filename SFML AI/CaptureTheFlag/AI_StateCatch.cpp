#include "AI_StateCatch.h"
#include "Game.h"

AI_StateCatch::AI_StateCatch()
{
}

AI_StateCatch::~AI_StateCatch()
{
}

void AI_StateCatch::Enter()
{
	sBehavior.SetBehavior(BEHAVIOR::SEEK);
	sBehavior2.SetBehavior(BEHAVIOR::FLOCKING);
}

AI_STATE_TYPE AI_StateCatch::Update(AI* _agent)
{
	auto& gameObj = GetGameObj();

	_agent->SetSteeringBehavior(BEHAVIOR::IDDLE);

	// ----- Steering 
	sBehavior.UpdateMovement(_agent, _agent->GetTarget(), gameObj.GetActorManager().GetActorsByType(ACTOR_TYPE::AI));
	sBehavior2.UpdateMovement(_agent, _agent->GetTarget(), gameObj.GetActorManager().GetActorsByType(ACTOR_TYPE::AI));

	sf::Vector2f steering = sBehavior.GetSteering();
	steering += sBehavior2.GetSteering();

	steering = (steering - _agent->GetVelocity()) * 0.1f;
	_agent->SetVelocity(_agent->GetVelocity() + steering);

	//_agent->Update();

	return AI_STATE_TYPE::AI_STATE_CATCH;

	//std::cout << "Unexpected Behavior" << std::endl;
}

void AI_StateCatch::Exit()
{
}
