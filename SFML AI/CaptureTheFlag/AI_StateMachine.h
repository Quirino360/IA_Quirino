#pragma once
#include "AI_State.h"
#include "AI_StateStart.h"
#include "AI_StateCatch.h"

#include "AI.h"

#include <map>


/**
* @brief   State machine for the AI steering beahaviors
* @bug     NA		*/
class AI_StateMachine
{
public:
	/**
	* @brief   default constructor
	* @param   NA
	* @bug     NA
	* @return  #void		*/
	AI_StateMachine();

	/**
	* @brief   releases memory
	* @param   NA
	* @bug     NA
	* @return  NA		*/
	~AI_StateMachine();

	/**
	* @brief   initializes variables
	* @param   #float move camera in axis x
	* @bug     NA
	* @return  #void		*/
	void Init();

	/**
	* @brief   updates the AI current state
	* @param   AI& agent to modify
	* @bug     NA
	* @return  #void		*/
	void Update(AI* _agent);

private:
	
	AI_STATE_TYPE currentState = AI_STATE_TYPE::AI_STATE_START;

	std::shared_ptr<AI_State> state;
	std::shared_ptr<AI_StateStart> stateStart;
	std::shared_ptr<AI_StateCatch> stateCatch;

	std::map<AI_STATE_TYPE, std::shared_ptr<AI_State>> stateMap;		

public:
	/**
	* @brief   Set the current state
	* @param   AI&  agent to modify curent state
	* @param   AI_STATE_TYPE  new state type
	* @bug     NA
	* @return  #void		*/
	void SetCurrentState(AI* _agent, AI_STATE_TYPE _newState);

	/**
	* @brief   gets the Current State
	* @param   NA
	* @bug     do not return the ai specified
	* @return  #std::shared_ptr<AI_State> new state		*/
	std::shared_ptr<AI_State> GetCurentState();
private:
};
