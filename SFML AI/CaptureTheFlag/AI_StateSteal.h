#pragma once
#include "AI_State.h"

/*
	CAPTURE_FLAG = 0,
	STEAL_FLAG,
	CARRY_FLAG_TO_BASE,
	COVER_FLAG_CARRIER
*/


/**
* @brief   Artificial Inteligence State Patrol
* @bug     NA	*/
class AI_StateSteal : public AI_State
{
public:
	/**
	* @brief   default constructor
	* @param   NA
	* @bug     NA
	* @return  #void		*/
	AI_StateSteal();

	/**
	* @brief   constructor
	* @param   #float new max velocity
	* @param   #float new max speed
	* @param   #float new max force
	* @param   #float new mass
	* @bug     NA
	* @return  #void		*/
	AI_StateSteal(float _maxVelocity, float _maxSpeed, float _maxForce, float _mass);

	/**
	* @brief   releases memory
	* @param   NA
	* @bug     NA
	* @return  NA		*/
	~AI_StateSteal();

private:
	SteeringBehavior sBehavior;

public:
	/**
	* @brief   what will do entering this state
	* @param   NA
	* @bug     NA
	* @return  #void		*/
	virtual void Enter();

	/**
	* @brief   updates the AI  behavior
	* @param   #gl::AI& agent to update
	* @bug     NA
	* @return  #void		*/
	virtual AI_STATE_TYPE Update(AI& _agent);

	/**
	* @brief   what will do leaving this state
	* @param   NA
	* @bug     NA
	* @return  #void		*/
	virtual void Exit();

	/**
	* @brief   gets the behavior vector velocity
	* @param   NA
	* @bug     NA
	* @return  sf::Vector2f behavior velocity		*/
	sf::Vector2f GetSteering() { return sBehavior.GetSteering(); };
private:
};

