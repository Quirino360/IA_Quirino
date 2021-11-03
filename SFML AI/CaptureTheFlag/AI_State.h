#pragma once
#include "SteeringBehavior.h"
#include "AI.h"


/**
* @brief   states of the AI state machine
* @bug     NA	*/
enum class AI_STATE_TYPE
{
	AI_STATE_IDDLE = 0,
	AI_STATE_SEEK,
	AI_STATE_FLEE,
	AI_STATE_ARRIVE,
	AI_STATE_PERSUIT,
	AI_STATE_EVADE,
	AI_STATE_WANDER,
	AI_STATE_PATH_FOLLOWING_LOOP,
	AI_STATE_PATH_FOLLOWING,
	AI_STATE_PATROL,
	AI_STATE_FLOCKING
};


/**
* @brief   Father class for the Artificial Inteligence States
* @bug     NA		*/
class AI_State
{
public: 
	/**
	* @brief   default constructor
	* @param   NA
	* @bug     NA
	* @return  #void		*/
	AI_State();

	/**
	* @brief   releases memory
	* @param   NA
	* @bug     NA
	* @return  NA		*/
	virtual ~AI_State();

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
	virtual AI_STATE_TYPE Update(AI* _agent) = 0;

	/**
	* @brief   what will do leaving this state
	* @param   NA
	* @bug     NA
	* @return  #void		*/
	virtual void Exit() = 0;

private:
};

