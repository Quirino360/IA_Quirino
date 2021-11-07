#pragma once
#include "SteeringBehavior.h"
#include "AI.h"


/**
* @brief   states of the AI state machine
* @bug     NA	*/
enum class PLAYER_STATE_TYPE
{
	PLAYER_STATE_START = 0,
	PLAYER_STATE_RUN
};


/**
* @brief   Father class for the Artificial Inteligence States
* @bug     NA		*/
class Player_State
{
public:
	/**
	* @brief   default constructor
	* @param   NA
	* @bug     NA
	* @return  #void		*/
	Player_State();

	/**
	* @brief   releases memory
	* @param   NA
	* @bug     NA
	* @return  NA		*/
	virtual ~Player_State();

private:

public:
	/**
	* @brief   what will do entering this state
	* @param   NA
	* @bug     NA
	* @return  #void		*/
	virtual void Enter() = 0;

	/**
	* @brief   updates the AI  behavior
	* @param   #gl::AI& agent to update
	* @bug     NA
	* @return  #void		*/
	virtual PLAYER_STATE_TYPE Update(Player* _agent) = 0;

	/**
	* @brief   what will do leaving this state
	* @param   NA
	* @bug     NA
	* @return  #void		*/
	virtual void Exit() = 0;

private:
};
