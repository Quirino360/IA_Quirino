#pragma once
#include "AI_State.h"
class AI_StatePatrol :  public AI_State
{
public:
	/**
	* @brief   default constructor
	* @param   NA
	* @bug     NA
	* @return  #void		*/
	AI_StatePatrol();

	/**
	* @brief   releases memory
	* @param   NA
	* @bug     NA
	* @return  NA		*/
	~AI_StatePatrol();

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
	virtual AI_STATE_TYPE Update(AI* _agent);

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

