#pragma once
#include <SFML/Graphics.hpp>


/**
* @brief   Father class for the Artificial Inteligence States
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
	PATH_FOLLOWING,
	COLLITION_AVOIDANCE,
	FLOCKING
};

/**
* @brief   Path point, to use in patrol beahvior
* @bug     NA
* @return  #void		*/
struct PathPoint
{
	sf::Vector2f position;
	float radius;
};

class Actor;

/**
* @brief   Manages the steering behavior to use
* @bug     NA
* @return  #void		*/
class SteeringBehavior
{
public:
	/**
	* @brief   default constructor
	* @param   NA
	* @bug     NA
	* @return  #void		*/
	SteeringBehavior();

	/**
	* @brief   releases memory
	* @param   NA
	* @bug     NA
	* @return  NA		*/
	~SteeringBehavior();

	/**
	* @brief   updates the forces of the steering behavior
	* @param   sf::Vector2f agent position
	* @param   sf::Vector2f target movement vectyor
	* @param   sf::Vector2f target position
	* @bug     NA
	* @return  #void		*/
	void UpdateMovement(Actor* _this, Actor* _target);

private:

	BEHAVIOR behavior = BEHAVIOR::IDDLE;

	//steering beahviors
	sf::Vector2f steering;


	// Wander ------------------------- 
	sf::Vector2f pathTarget;

	// Path folowing ------------------------- 
	std::vector<PathPoint> nodes;
	int nodeID = 0;
	PathPoint pathPointTarget;

public:

	// ----- Getters 
	/**
	* @brief   gets current behavior
	* @param   NA
	* @bug     NA
	* @return  #BEHAVIOR current behavior		*/
	BEHAVIOR GetBehavior() { return behavior; };

	/**
	* @brief   gets current velocity
	* @param   NA
	* @bug     NA
	* @return  #sf::Vector2f current velocity		*/
	sf::Vector2f GetSteering() { return steering; };

	// ----- Setters 
	/**
	* @brief   sets current Behavior
	* @param   #BEHAVIOR new current behavior
	* @bug     NA
	* @return  #void		*/
	void SetBehavior(BEHAVIOR _newBehavior) { behavior = _newBehavior; };


private:
	// ----- Steering Behaviors 
	/**
	* @brief   steering behavior seek
	* @param   sf::Vector2f agent position
	* @param   sf::Vector2f target position
	* @bug     NA
	* @return  #sf::Vector2f behavior new velocity		*/
	void SteeringBehaiviorSeek(Actor* _this, Actor* _target);

	/**
	* @brief   steering behavior flee
	* @param   sf::Vector2f agent position
	* @param   sf::Vector2f target position
	* @bug     NA
	* @return  #sf::Vector2f behavior new velocity		*/
	void SteeringBehaiviorFlee(Actor* _this, Actor* _target);

	/**
	* @brief   steering behavior seek
	* @param   sf::Vector2f agent position
	* @param   sf::Vector2f target position
	* @bug     NA
	* @return  #sf::Vector2f behavior new velocity		*/
	void SteeringBehaiviorArrival(Actor* _this, Actor* _target);

	/**
	* @brief   steering behavior seek
	* @param   sf::Vector2f agent position
	* @bug     NA
	* @return  #sf::Vector2f behavior new velocity		*/
	void SteeringBehaiviorWander(Actor* _this); //Mejorar collition y la manera de hacerlo

	/**
	* @brief   steering behavior seek
	* @param   sf::Vector2f agent position
	* @param   sf::Vector2f target movement vectyor
	* @param   sf::Vector2f target position
	* @bug     NA
	* @return  #sf::Vector2f behavior new velocity		*/
	void SteeringBehaiviorPersuit(Actor* _this, Actor* _target);

	/**
	* @brief   steering behavior seek
	* @param   sf::Vector2f agent position
	* @param   sf::Vector2f target movement vectyor
	* @param   sf::Vector2f target position
	* @bug     NA
	* @return  #sf::Vector2f behavior new velocity		*/
	void SteeringBehaiviorEvade(Actor* _this, Actor* _target);

	/**
	* @brief   steering behavior seek
	* @param   sf::Vector2f agent position
	* @bug     NA
	* @return  #sf::Vector2f behavior new velocity		*/
	void SteeringBehaviorPathFollowing(Actor* _this);


	
	
	// Path folowing ------------------------- 
		/**
	* @brief   adds a path point to the patrol route
	* @param   #PathPoint new path point
	* @bug     NA
	* @return  #void		*/
	void AddPathPoint(PathPoint _point) { nodes.push_back(_point); };
		
	/**
	* @brief   Creates a default patrol route if the user doesnt
	* @param   sf::Vector2f agent position
	* @bug     NA
	* @return  #void		*/
	void CreateDefaultPath(sf::Vector2f _thisPostion);

	/**
	* @brief   sets new patrol route
	* @param   #std::vector<PathPoint path pont to follow
	* @bug     NA
	* @return  #void		*/
	void SetPath(std::vector<PathPoint> newPathPoints);

	/**
	* @brief   gets the next path point ID to follow
	* @param   NA
	* @bug     NA
	* @return  #int path point ID		*/
	int GetNextPointID();
};
