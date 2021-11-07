#include "AI_StateMachine.h"



AI_StateMachine::AI_StateMachine()
{

}

AI_StateMachine::~AI_StateMachine()
{

}

void AI_StateMachine::Init()
{
	// ----- 
	stateStart = std::make_shared<AI_StateStart>();
	stateCatch = std::make_shared<AI_StateCatch>();
	

	// ----- 
	stateMap.insert(std::pair<AI_STATE_TYPE, std::shared_ptr<AI_State>>(AI_STATE_TYPE::AI_STATE_START, static_cast<std::shared_ptr<AI_State>>(stateStart)));
	stateMap.insert(std::pair<AI_STATE_TYPE, std::shared_ptr<AI_State>>(AI_STATE_TYPE::AI_STATE_CATCH, static_cast<std::shared_ptr<AI_State>>(stateCatch)));

	state = stateMap.find(AI_STATE_TYPE::AI_STATE_START)->second;
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
		state = stateMap.find(AI_STATE_TYPE::AI_STATE_START)->second;
		state->Enter();
	}
	return state;
}
