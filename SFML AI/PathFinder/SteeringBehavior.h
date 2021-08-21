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
	* @brief   constructor
	* @param   #float new max velocity
	* @param   #float new max speed
	* @param   #float new max force
	* @param   #float new mass
	* @bug     NA
	* @return  #void		*/
	SteeringBehavior(float _maxVelocity, float _maxSpeed, float _maxForce, float _mass);

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
	void UpdateMovement(sf::Vector2f _thisPostion, sf::Vector2f _targetMovement, sf::Vector2f _targetPosition);

private:

	BEHAVIOR behavior = BEHAVIOR::IDDLE;

	//steering beahviors
	sf::Vector2f velocity, desiredVelocity, steering; //used in seek, flee
	float maxVelocity = 2;  
	float maxSpeed = 2;	
	float maxForce = 2;
	float mass = 1;

	// Wander ------------------------- 
	sf::Vector2f pathTarget;

	// Path folowing ------------------------- 
	std::vector<PathPoint> nodes;
	int nodeID = 0;
	PathPoint pathPointTarget;

public:
	/**
	* @brief   gets the ddistance of bwetteen 2 vectors
	* @param   #sf::Vector2f A
	* @param   #sf::Vector2f B
	* @bug     NA
	* @return  #float vectors distance		*/
	static float DistanceBetweenVectors(sf::Vector2f A, sf::Vector2f B);

	// ------------------------- Getters ------------------------- //
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
	sf::Vector2f GetVelocity() { return velocity; };

	// ------------------------- Setters ------------------------- //
	/**
	* @brief   sets current Behavior
	* @param   #BEHAVIOR new current behavior
	* @bug     NA
	* @return  #void		*/
	void SetBehavior(BEHAVIOR _newBehavior) { behavior = _newBehavior; };


private:
	// ------------------------- Steering Behaviors ------------------------- //
	/**
	* @brief   steering behavior seek
	* @param   sf::Vector2f agent position
	* @param   sf::Vector2f target position
	* @bug     NA
	* @return  #sf::Vector2f behavior new velocity		*/
	sf::Vector2f SteeringBehaiviorSeek(sf::Vector2f _thisPostion, sf::Vector2f _targetPosition);

	/**
	* @brief   steering behavior flee
	* @param   sf::Vector2f agent position
	* @param   sf::Vector2f target position
	* @bug     NA
	* @return  #sf::Vector2f behavior new velocity		*/
	sf::Vector2f SteeringBehaiviorFlee(sf::Vector2f _thisPostion, sf::Vector2f _targetPosition);

	/**
	* @brief   steering behavior seek
	* @param   sf::Vector2f agent position
	* @param   sf::Vector2f target position
	* @bug     NA
	* @return  #sf::Vector2f behavior new velocity		*/
	sf::Vector2f SteeringBehaiviorArrival(sf::Vector2f _thisPostion, sf::Vector2f _targetPosition);

	/**
	* @brief   steering behavior seek
	* @param   sf::Vector2f agent position
	* @bug     NA
	* @return  #sf::Vector2f behavior new velocity		*/
	sf::Vector2f SteeringBehaiviorWander(sf::Vector2f _thisPostion); //Mejorar collition y la manera de hacerlo

	/**
	* @brief   steering behavior seek
	* @param   sf::Vector2f agent position
	* @param   sf::Vector2f target movement vectyor
	* @param   sf::Vector2f target position
	* @bug     NA
	* @return  #sf::Vector2f behavior new velocity		*/
	sf::Vector2f SteeringBehaiviorPersuit(sf::Vector2f _thisPostion, sf::Vector2f _targetPosition, sf::Vector2f _targetMovement); 

	/**
	* @brief   steering behavior seek
	* @param   sf::Vector2f agent position
	* @param   sf::Vector2f target movement vectyor
	* @param   sf::Vector2f target position
	* @bug     NA
	* @return  #sf::Vector2f behavior new velocity		*/
	sf::Vector2f SteeringBehaiviorEvade(sf::Vector2f _thisPostion, sf::Vector2f _targetPosition, sf::Vector2f _targetMovement);

	/**
	* @brief   steering behavior seek
	* @param   sf::Vector2f agent position
	* @bug     NA
	* @return  #sf::Vector2f behavior new velocity		*/
	sf::Vector2f SteeringBehaviorPathFollowing(sf::Vector2f _thisPostion);


	// MathFunctions ------------------------- 
	/**
	* @brief   normalizes a 2 dimecional vector
	* @param   sf::Vector2f vetor to normalize
	* @bug     NA
	* @return  #sf::Vector2f vector normalized		*/
	sf::Vector2f NormalizeVector(sf::Vector2f A);

	/**
	* @brief   normalizes a 2 dimecional vector and multyplies it
	* @param   sf::Vector2f vetor to normalize and multiply
	* @bug     NA
	* @return  #sf::Vector2f vector normalized and multiplied	*/
	sf::Vector2f TruncateVector(sf::Vector2f A, float x);



	/**
	* @brief   lenght of a 2 dimencional vector
	* @param   sf::Vector2f vector to get lenght
	* @bug     NA
	* @return  #float vector lenght		*/
	float VectorLenght(sf::Vector2f A); //magnitude
	
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

/*
	
	//this has to be in the ai steering behavior
	void SteeringBehaviorAIAvoidancePersuitPlayer(Player _target, std::vector<AI> _obstacles);
	void SteeringBehaviorAIAvoidancePersuitFlag(Flag _target, std::vector<AI> _obstacles); // Capture the flag
	void SteeringBehaviorAIAvoidanceFleeIA(AI _target, std::vector<AI> _obstacles); // Capture the flag
	void SteeringBehaviorAIAvoidancePersuitAI(AI _target, std::vector<AI> _obstacles); // Capture the flag
	bool IsOnSight(std::vector<Player> players);
	void findMostThreateningObstacle(sf::Vector2f _ahead, sf::Vector2f _ahead2, std::vector<sf::CircleShape> _obstacles);
	AI NearestAI(std::vector<AI> _obstacles);
	bool lineIntersectsObstacle(sf::Vector2f _ahead, sf::Vector2f _ahead2, sf::CircleShape obstacle);

*/