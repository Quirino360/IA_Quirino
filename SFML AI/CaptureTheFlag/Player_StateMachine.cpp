#include "Player_StateMachine.h"

Player_StateMachine::Player_StateMachine()
{
}

Player_StateMachine::~Player_StateMachine()
{
}

void Player_StateMachine::Init()
{
	// ----- 
	 stateStart = std::make_shared<Player_StateStart>();
	 stateCatch = std::make_shared<Player_StateRun>();


	// ----- 
	stateMap.insert(std::pair<PLAYER_STATE_TYPE, std::shared_ptr<Player_State>>(PLAYER_STATE_TYPE::PLAYER_STATE_START, static_cast<std::shared_ptr<Player_State>>(stateCatch)));
	stateMap.insert(std::pair<PLAYER_STATE_TYPE, std::shared_ptr<Player_State>>(PLAYER_STATE_TYPE::PLAYER_STATE_RUN, static_cast<std::shared_ptr<Player_State>>(stateCatch)));

	state = stateMap.find(PLAYER_STATE_TYPE::PLAYER_STATE_START)->second;
	state->Enter();
}

void Player_StateMachine::Update(Player* _agent)
{
	// 2048 * 1080 -> 1024, 540

	currentState = *_agent->playerState;
	state = stateMap.find(currentState)->second;

	PLAYER_STATE_TYPE newState = state->Update(_agent);
	if (newState != currentState)
	{
		SetCurrentState(_agent, newState);
	}
}

void Player_StateMachine::SetCurrentState(Player* _agent, PLAYER_STATE_TYPE _newState)
{
	if (nullptr == state)
	{
		state = stateMap.find(_newState)->second;
		state->Enter();
	}
	else
	{
		state->Exit();
		state = stateMap.find(_newState)->second;
		*_agent->playerState = _newState;
		state->Enter();
	}

	currentState = _newState;
}

std::shared_ptr<Player_State> Player_StateMachine::GetCurentState()
{
	if (nullptr == state)
	{
		state = stateMap.find(PLAYER_STATE_TYPE::PLAYER_STATE_START)->second;
		state->Enter();
	}
	return state;
}
