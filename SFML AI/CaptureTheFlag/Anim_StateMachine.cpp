#include "Anim_StateMachine.h"


Anim_StateMachine::Anim_StateMachine()
{
}

Anim_StateMachine::~Anim_StateMachine()
{
}

void Anim_StateMachine::Init()
{
	stateDefeat = std::make_shared<Anim_StateDefeat>();
	stateIdle = std::make_shared<Anim_StateIdle>();
	stateRun = std::make_shared<Anim_StateRun>();

	stateWalkUp = std::make_shared<Anim_StateWalkUp>();
	stateWalkDown = std::make_shared<Anim_StateWalkDown>();
	stateWalkLeft = std::make_shared<Anim_StateWalkLeft>();
	stateWalkRight = std::make_shared<Anim_StateWalkRight>();



	stateMap.insert(std::pair<ANIMATION_AI_STATE_TYPE, std::shared_ptr<Anim_State>>(ANIMATION_AI_STATE_TYPE::DEFEAT, static_cast<std::shared_ptr<Anim_State>>(stateDefeat)));
	stateMap.insert(std::pair<ANIMATION_AI_STATE_TYPE, std::shared_ptr<Anim_State>>(ANIMATION_AI_STATE_TYPE::IDLE, static_cast<std::shared_ptr<Anim_State>>(stateIdle)));
	stateMap.insert(std::pair<ANIMATION_AI_STATE_TYPE, std::shared_ptr<Anim_State>>(ANIMATION_AI_STATE_TYPE::RUN, static_cast<std::shared_ptr<Anim_State>>(stateRun)));

	stateMap.insert(std::pair<ANIMATION_AI_STATE_TYPE, std::shared_ptr<Anim_State>>(ANIMATION_AI_STATE_TYPE::WALK_UP, static_cast<std::shared_ptr<Anim_State>>(stateWalkUp)));
	stateMap.insert(std::pair<ANIMATION_AI_STATE_TYPE, std::shared_ptr<Anim_State>>(ANIMATION_AI_STATE_TYPE::WALK_DOWN, static_cast<std::shared_ptr<Anim_State>>(stateWalkDown)));
	stateMap.insert(std::pair<ANIMATION_AI_STATE_TYPE, std::shared_ptr<Anim_State>>(ANIMATION_AI_STATE_TYPE::WALK_LEFT, static_cast<std::shared_ptr<Anim_State>>(stateWalkLeft)));
	stateMap.insert(std::pair<ANIMATION_AI_STATE_TYPE, std::shared_ptr<Anim_State>>(ANIMATION_AI_STATE_TYPE::WALK_RIGHT, static_cast<std::shared_ptr<Anim_State>>(stateWalkRight)));

	state = stateMap.find(ANIMATION_AI_STATE_TYPE::IDLE)->second;
}

void Anim_StateMachine::Update(AI* _agent)
{
	// 2048 * 1080 -> 1024, 540
	currentState = *_agent->GetAnimationStateType();
	
	state = stateMap.find(currentState)->second;

	ANIMATION_AI_STATE_TYPE newState = state->Update(_agent);
	if (newState != currentState)
	{
		SetCurrentState(_agent, newState);
	}
}

void Anim_StateMachine::SetCurrentState(AI* _agent, ANIMATION_AI_STATE_TYPE _newState)
{
	if (nullptr == state)
	{
		state = stateMap.find(_newState)->second;
		state->Enter(_agent);
	}
	else
	{
		state->Exit(_agent);
		state = stateMap.find(_newState)->second;
		*_agent->GetAnimationStateType() = _newState;
		state->Enter(_agent);
	}

	currentState = _newState;
}

std::shared_ptr<Anim_State> Anim_StateMachine::GetCurentState(AI* _agent)
{
	if (nullptr == state)
	{
		state = stateMap.find(ANIMATION_AI_STATE_TYPE::IDLE)->second;
		state->Enter(_agent);
	}
	return state;
}
