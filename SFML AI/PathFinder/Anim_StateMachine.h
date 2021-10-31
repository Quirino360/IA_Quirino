#pragma once
#include "Anim_State.h"

#include "Anim_StateDefeat.h"
#include "Anim_StateIdle.h"
#include "Anim_StateRun.h"
#include "Anim_StateWalkUp.h"
#include "Anim_StateWalkDown.h"
#include "Anim_StateWalkLeft.h"
#include "Anim_StateWalkRight.h"

#include "AI.h"

#include <map>

namespace gl 
{
	class Anim_StateMachine
	{
	public:
		Anim_StateMachine();
		~Anim_StateMachine();

		void Init();
		void Update(AI* _agent);

	private:

		ANIMATION_AI_STATE_TYPE currentState = ANIMATION_AI_STATE_TYPE::IDLE;

		std::shared_ptr<Anim_State> state;

		/*
		#include "Anim_StateDefeat.h"
		#include "Anim_StateIdle.h"
		#include "Anim_StateRun.h"
		#include "Anim_StateWalkUp.h"
		*/

		std::shared_ptr<Anim_StateDefeat> stateDefeat;
		std::shared_ptr<Anim_StateIdle> stateIdle;
		std::shared_ptr<Anim_StateRun> stateRun;
		std::shared_ptr<Anim_StateWalkUp> stateWalkUp;
		std::shared_ptr<Anim_StateWalkDown> stateWalkDown;
		std::shared_ptr<Anim_StateWalkLeft> stateWalkLeft;
		std::shared_ptr<Anim_StateWalkRight> stateWalkRight;

		std::map<ANIMATION_AI_STATE_TYPE, std::shared_ptr<Anim_State>> stateMap;
		//1 = stateCapture	2 = stateCarry	3 = stateCover	4 = stateSteal			

	public:
		void SetCurrentState(AI* _agent, ANIMATION_AI_STATE_TYPE _newState);
		std::shared_ptr<Anim_State> GetCurentState(AI* _agent);

	private:
	};

}

