#include "AI_StateStart.h"

AI_StateStart::AI_StateStart()
{
}

AI_StateStart::~AI_StateStart()
{
}

void AI_StateStart::Enter()
{
	sBehavior.SetBehavior(BEHAVIOR::IDDLE);
}

AI_STATE_TYPE AI_StateStart::Update(AI* _agent)
{
	if (_agent->GetSteeringBehavior().GetBehavior() != sBehavior.GetBehavior());
	_agent->GetSteeringBehavior().SetBehavior(sBehavior.GetBehavior());/**/

	//_agent->Update();

	return AI_STATE_TYPE::AI_STATE_CATCH;

	//std::cout << "Unexpected Behavior" << std::endl;
}

void AI_StateStart::Exit()
{
}
