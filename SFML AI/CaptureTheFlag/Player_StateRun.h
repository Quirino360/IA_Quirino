#pragma once
#include "Player_State.h"

class Player_StateRun :  public Player_State
{
public:
	/**
* @brief   default constructor
* @param   NA
* @bug     NA
* @return  #void		*/
	Player_StateRun();

	/**
	* @brief   releases memory
	* @param   NA
	* @bug     NA
	* @return  NA		*/
	~Player_StateRun();

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
	virtual PLAYER_STATE_TYPE Update(Player* _agent);

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
};

