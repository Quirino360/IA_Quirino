#pragma once
#include "Player_State.h"
#include "Player_StateStart.h"
#include "Player_StateRun.h"

#include "Player.h"

#include <map>



/**
* @brief   State machine for the AI steering beahaviors
* @bug     NA		*/
class Player_StateMachine
{
public:
	/**
	* @brief   default constructor
	* @param   NA
	* @bug     NA
	* @return  #void		*/
	Player_StateMachine();

	/**
	* @brief   releases memory
	* @param   NA
	* @bug     NA
	* @return  NA		*/
	~Player_StateMachine();

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
	void Update(Player* _agent);

private:

	PLAYER_STATE_TYPE currentState = PLAYER_STATE_TYPE::PLAYER_STATE_START;

	std::shared_ptr<Player_State> state;
	std::shared_ptr<Player_StateStart> stateStart;
	std::shared_ptr<Player_StateRun> stateCatch;

	std::map<PLAYER_STATE_TYPE, std::shared_ptr<Player_State>> stateMap;

public:
	/**
	* @brief   Set the current state
	* @param   AI&  agent to modify curent state
	* @param   AI_STATE_TYPE  new state type
	* @bug     NA
	* @return  #void		*/
	void SetCurrentState(Player* _agent, PLAYER_STATE_TYPE _newState);

	/**
	* @brief   gets the Current State
	* @param   NA
	* @bug     do not return the ai specified
	* @return  #std::shared_ptr<AI_State> new state		*/
	std::shared_ptr<Player_State> GetCurentState();
private:
};
