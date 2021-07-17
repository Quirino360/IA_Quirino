#include "AI_StateMachine.h"


namespace gl
{

	AI_StateMachine::AI_StateMachine()
	{

	}

	AI_StateMachine::~AI_StateMachine()
	{

	}

	void AI_StateMachine::Init()
	{
		stateCapture = std::make_shared<AI_StateCapture>();
		stateCarry = std::make_shared<AI_StateCarryBase>();
		stateCover = std::make_shared<AI_StateCover>();
		stateSteal = std::make_shared<AI_StateSteal>();

		stateMap.insert(std::pair<AI_STATE_TYPE, std::shared_ptr<AI_State>>(AI_STATE_TYPE::CAPTURE_FLAG, static_cast<std::shared_ptr<AI_State>>(stateCapture)));
		stateMap.insert(std::pair<AI_STATE_TYPE, std::shared_ptr<AI_State>>(AI_STATE_TYPE::CARRY_FLAG_TO_BASE, static_cast<std::shared_ptr<AI_State>>(stateCarry)));
		stateMap.insert(std::pair<AI_STATE_TYPE, std::shared_ptr<AI_State>>(AI_STATE_TYPE::COVER_FLAG_CARRIER, static_cast<std::shared_ptr<AI_State>>(stateCover)));
		stateMap.insert(std::pair<AI_STATE_TYPE, std::shared_ptr<AI_State>>(AI_STATE_TYPE::STEAL_FLAG, static_cast<std::shared_ptr<AI_State>>(stateSteal)));

		state = stateMap.find(AI_STATE_TYPE::CAPTURE_FLAG)->second;
		state->Enter();
	}

	void AI_StateMachine::Update(AI& _agent)
	{
		// 2048 * 1080 -> 1024, 540
		currentState = *_agent.AI_State;
		state = stateMap.find(currentState)->second;

		AI_STATE_TYPE newState = state->Update(_agent);
		if (newState != currentState)
		{
			SetCurrentState(_agent, newState);
		}
	}

	void AI_StateMachine::SetCurrentState(gl::AI& _agent, AI_STATE_TYPE _newState)
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
			*_agent.AI_State = _newState;
			state->Enter();
		}

		currentState = _newState;
	}

	std::shared_ptr<AI_State> AI_StateMachine::GetCurentState()
	{
		if (nullptr == state)
		{
			state = stateMap.find(AI_STATE_TYPE::CAPTURE_FLAG)->second;
			state->Enter();
		}
		return state;
	}
}