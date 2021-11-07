#include "Player_StateStart.h"

Player_StateStart::Player_StateStart()
{
}

Player_StateStart::~Player_StateStart()
{
}

void Player_StateStart::Enter()
{
	sBehavior.SetBehavior(BEHAVIOR::IDDLE);
}

PLAYER_STATE_TYPE Player_StateStart::Update(Player* _agent)
{
	if (_agent->GetSteeringBehavior().GetBehavior() != sBehavior.GetBehavior());
	_agent->GetSteeringBehavior().SetBehavior(sBehavior.GetBehavior());/**/

	//_agent->Update();

	return PLAYER_STATE_TYPE::PLAYER_STATE_RUN;

	//std::cout << "Unexpected Behavior" << std::endl;
}

void Player_StateStart::Exit()
{
}
