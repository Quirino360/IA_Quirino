#include "Player_StateRun.h"

Player_StateRun::Player_StateRun()
{
}

Player_StateRun::~Player_StateRun()
{
}

void Player_StateRun::Enter()
{
	sBehavior.SetBehavior(BEHAVIOR::WANDER);
}

PLAYER_STATE_TYPE Player_StateRun::Update(Player* _agent)
{
	if (_agent->GetSteeringBehavior().GetBehavior() != sBehavior.GetBehavior());
	_agent->GetSteeringBehavior().SetBehavior(sBehavior.GetBehavior());/**/

	//_agent->Update();

	return PLAYER_STATE_TYPE::PLAYER_STATE_RUN;

	//std::cout << "Unexpected Behavior" << std::endl;
}

void Player_StateRun::Exit()
{
}
