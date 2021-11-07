#pragma once
#include <SFML/Graphics.hpp>
#include "Actor.h"

/**
* @brief   Father class for the Artificial Intelligence States
* @bug     NA
* @return  #void		*/
enum class BEHAVIOR
{
	IDDLE = 0,
	SEEK, 
	FLEE, 
	ARRIVE, 
	PERSUIT, 
	EVADE,
	WANDER,
	PATH_FOLLOWING_LOOP,
	PATH_FOLLOWING,
	PATROL,
	FLOCKING
};

class Actor;




/**
* @brief   Manages the steering behavior to use
* @bug     NA
* @return  #void		*/
class SteeringBehavior
{
public:

	SteeringBehavior();
	~SteeringBehavior();

	void UpdateMovement(Actor* _this, Actor* _target, std::vector<Actor*> _other = std::vector<Actor*>());
	virtual void Render(sf::RenderWindow* window);

private:

	BEHAVIOR behavior = BEHAVIOR::IDDLE;

	// Steering force
	sf::Vector2f steering;


	// Wander  
	Actor* wanderTarget = new Actor();

	// ----- Path following  & Patrol
	std::vector<Actor> pathPoints;
	int pathID = 0;

	// Wnader
	float timer = 4;
public:

	BEHAVIOR GetBehavior() { return behavior; };
	sf::Vector2f GetSteering() { return steering; };

	void SetBehavior(BEHAVIOR _newBehavior) { behavior = _newBehavior; };


private:

	void SteeringBehaiviorSeek(Actor* _this, Actor* _target);

	void SteeringBehaiviorFlee(Actor* _this, Actor* _target);

	void SteeringBehaiviorArrival(Actor* _this, Actor* _target);

	void SteeringBehaiviorWander(Actor* _this); 

	void SteeringBehaiviorPersuit(Actor* _this, Actor* _target);

	void SteeringBehaiviorEvade(Actor* _this, Actor* _target);

	void SteeringBehaviorPathFollowingLoop(Actor* _this);

	void SteeringBehaviorPathFollowing(Actor* _this);
	
	void SteeringBehaviorPatrol(Actor* _this);

	void SteeringBehaviorFlocking(Actor* _this, std::vector<Actor*> _other);


	void AddPathPoint(Actor _point) { pathPoints.push_back(_point); };
	void CreateDefaultPath(sf::Vector2f _thisPostion);
	int SetNextPointID(bool _isPatrol);
};
