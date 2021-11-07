#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Actor.h"
#include "Player.h"
#include "Flag.h"
#include "SteeringBehavior.h"

enum class AI_STATE_TYPE;

/**
* @brief   manages the Artificial Intelligence behaviors
* @bug     NA	*/
class AI : public Actor
{
public:

	AI();
	~AI();

	virtual void Init(sf::Vector2f _position = { 0.0f, 0.0f }, bool setTexture = true);
	virtual void Update();
	virtual void Render(sf::RenderWindow* window);
	virtual void Destroy();

	//
	AI_STATE_TYPE* AI_State;

	// ----- Capture the flag
	bool enemyHasFlag = false;
	bool alliesHasFlag = false;
	bool hasFlag = false; // change to true if it has the flag 
	bool restart = false;
	unsigned int gameResult = 0; // NA = 0, Win = 1, Loose = 2;

private:

	bool hasTargetAI = false;

	// Capture the flag
	Actor* target = nullptr;
	std::vector<AI>* allies;
	std::vector<AI>* enemies;
	sf::CircleShape* goal;
	Flag* flag;

	// Steering Behavior
	SteeringBehavior sBehavior;
	

public:
	void UpdateFlag();

	// ----- Getters
	// ----- Capture the flag
	Actor* GetTarget() { return target; };
	std::vector<AI>* GetAllies() { return allies; };
	std::vector<AI>* GetEnemies() { return enemies; };
	sf::CircleShape* GetGoal() { return goal; };
	Flag* GetFlag() { return flag; };

	// Steering Behavior
	SteeringBehavior& GetSteeringBehavior() { return sBehavior; };


	// ----- Setters
	// ----- Capture the flag
	void SetTarget(Actor* _newTarget) { target = _newTarget; };
	void SetSteeringBehavior(BEHAVIOR _newBehavior) { sBehavior.SetBehavior(_newBehavior); };
	void SetCircleColor(sf::Color _newColor) { cShape.setFillColor(_newColor); };

	void SetEnemies(std::vector<AI>& _enemies) {
		if (enemies != nullptr) {
			delete enemies;
			enemies = &_enemies;
		}
		else {
			enemies = &_enemies;
		}
	};

	void SetAllies(std::vector<AI>& _allies) {
		if (allies != nullptr) {
			delete allies;
			allies = &_allies;
		}
		else {
			allies = &_allies;
		}
	};


private:

	bool TouchedFlag();
	bool TouchedGoal();
	bool lineIntersectsAI(sf::Vector2f _ahead, sf::Vector2f _ahead2, AI obstacle); // Capture the flag
	AI findMostThreateningAI(sf::Vector2f _ahead, sf::Vector2f _ahead2); // Capture the flag

};
