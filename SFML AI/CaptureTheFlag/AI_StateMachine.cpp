#include "AI_StateMachine.h"



AI_StateMachine::AI_StateMachine()
{

}

AI_StateMachine::~AI_StateMachine()
{

}

/*
	std::shared_ptr<AI_State> state;
	std::shared_ptr<AI_StateArrive> stateArrive;
	std::shared_ptr<AI_StateEvade> stateEvade;

	std::shared_ptr<AI_StateFlee> stateFlee;
	std::shared_ptr<AI_StateFlocking> stateFlocking;
	std::shared_ptr<AI_StateIddle> stateIddle;

	std::shared_ptr<AI_StatePathFollowing> statePathFollowing;
	std::shared_ptr<AI_StatePathFollowingLoop> statePathFollowingLopp;
	std::shared_ptr<AI_StatePatrol> stateStatePatrol;

	std::shared_ptr<AI_StatePersuit> statePersuit;
	std::shared_ptr<AI_StateSeek> stateSeek;
*/
void AI_StateMachine::Init()
{
	// ----- 
	stateArrive = std::make_shared<AI_StateArrive>();
	stateEvade = std::make_shared<AI_StateEvade>();
	stateFlee = std::make_shared<AI_StateFlee>();

	stateFlocking = std::make_shared<AI_StateFlocking>();
	stateIddle = std::make_shared<AI_StateIddle>();
	statePathFollowing = std::make_shared<AI_StatePathFollowing>();

	statePathFollowingLopp = std::make_shared<AI_StatePathFollowingLoop>();
	stateStatePatrol = std::make_shared<AI_StatePatrol>();
	statePersuit = std::make_shared<AI_StatePersuit>();

	stateSeek = std::make_shared<AI_StateSeek>();

	// ----- 
	stateMap.insert(std::pair<AI_STATE_TYPE, std::shared_ptr<AI_State>>(AI_STATE_TYPE::AI_STATE_ARRIVE, static_cast<std::shared_ptr<AI_State>>(stateArrive)));
	stateMap.insert(std::pair<AI_STATE_TYPE, std::shared_ptr<AI_State>>(AI_STATE_TYPE::AI_STATE_EVADE, static_cast<std::shared_ptr<AI_State>>(stateEvade)));
	stateMap.insert(std::pair<AI_STATE_TYPE, std::shared_ptr<AI_State>>(AI_STATE_TYPE::AI_STATE_FLEE, static_cast<std::shared_ptr<AI_State>>(stateFlee)));

	stateMap.insert(std::pair<AI_STATE_TYPE, std::shared_ptr<AI_State>>(AI_STATE_TYPE::AI_STATE_FLOCKING, static_cast<std::shared_ptr<AI_State>>(stateFlocking)));
	stateMap.insert(std::pair<AI_STATE_TYPE, std::shared_ptr<AI_State>>(AI_STATE_TYPE::AI_STATE_IDDLE, static_cast<std::shared_ptr<AI_State>>(stateIddle)));
	stateMap.insert(std::pair<AI_STATE_TYPE, std::shared_ptr<AI_State>>(AI_STATE_TYPE::AI_STATE_PATH_FOLLOWING, static_cast<std::shared_ptr<AI_State>>(statePathFollowing)));

	stateMap.insert(std::pair<AI_STATE_TYPE, std::shared_ptr<AI_State>>(AI_STATE_TYPE::AI_STATE_PATH_FOLLOWING_LOOP, static_cast<std::shared_ptr<AI_State>>(statePathFollowingLopp)));
	stateMap.insert(std::pair<AI_STATE_TYPE, std::shared_ptr<AI_State>>(AI_STATE_TYPE::AI_STATE_PATROL, static_cast<std::shared_ptr<AI_State>>(stateStatePatrol)));
	stateMap.insert(std::pair<AI_STATE_TYPE, std::shared_ptr<AI_State>>(AI_STATE_TYPE::AI_STATE_PERSUIT, static_cast<std::shared_ptr<AI_State>>(statePersuit)));

	stateMap.insert(std::pair<AI_STATE_TYPE, std::shared_ptr<AI_State>>(AI_STATE_TYPE::AI_STATE_SEEK, static_cast<std::shared_ptr<AI_State>>(stateSeek)));

	state = stateMap.find(AI_STATE_TYPE::AI_STATE_IDDLE)->second;
	state->Enter();
}

void AI_StateMachine::Update(AI* _agent)
{
	// 2048 * 1080 -> 1024, 540
	
	currentState = *_agent->AI_State;
	state = stateMap.find(currentState)->second;

	AI_STATE_TYPE newState = state->Update(_agent);
	if (newState != currentState)
	{
		SetCurrentState(_agent, newState);
	}
}

void AI_StateMachine::SetCurrentState(AI* _agent, AI_STATE_TYPE _newState)
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
		*_agent->AI_State = _newState;
		state->Enter();
	}

	currentState = _newState;
}

std::shared_ptr<AI_State> AI_StateMachine::GetCurentState()
{
	if (nullptr == state)
	{
		state = stateMap.find(AI_STATE_TYPE::AI_STATE_IDDLE)->second;
		state->Enter();
	}
	return state;
}
