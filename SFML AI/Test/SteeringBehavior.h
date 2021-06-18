#pragma once
#include <SFML/Graphics.hpp>

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

struct PathPoint
{
	sf::Vector2f position;
	float radius;
};

class SteeringBehavior
{
public:
	SteeringBehavior();
	SteeringBehavior(float _maxVelocity, float _maxSpeed, float _maxForce, float _mass);
	~SteeringBehavior();

	//Depending on the steering directions it returns the direction
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
	// ------------------------- Getters ------------------------- //
	BEHAVIOR GetBehavior() { return behavior; };
	sf::Vector2f GetVelocity() { return velocity; };

	// ------------------------- Getters ------------------------- //
	void SetBehavior(BEHAVIOR _newBehavior) { behavior = _newBehavior; };
private:

	sf::Vector2f SteeringBehaiviorSeek(sf::Vector2f _thisPostion, sf::Vector2f _targetPosition);
	sf::Vector2f SteeringBehaiviorFlee(sf::Vector2f _thisPostion, sf::Vector2f _targetPosition);
	sf::Vector2f SteeringBehaiviorArrival(sf::Vector2f _thisPostion, sf::Vector2f _targetPosition);
	sf::Vector2f SteeringBehaiviorWander(sf::Vector2f _thisPostion); //Mejorar collition y la manera de hacerlo
	sf::Vector2f SteeringBehaiviorPersuit(sf::Vector2f _thisPostion, sf::Vector2f _targetPosition, sf::Vector2f _targetMovement); // 
	sf::Vector2f SteeringBehaiviorEvade(sf::Vector2f _thisPostion, sf::Vector2f _targetPosition, sf::Vector2f _targetMovement);
	sf::Vector2f SteeringBehaviorPathFollowing(sf::Vector2f _thisPostion);


	// MathFunctions ------------------------- 
	sf::Vector2f NormalizeVector(sf::Vector2f A);
	sf::Vector2f TruncateVector(sf::Vector2f A, float x);
	float DistanceBetweenVectors(sf::Vector2f A, sf::Vector2f B);
	float VectorLenght(sf::Vector2f A); //magnitude
	
	// Path folowing ------------------------- 
	void AddPathPoint(PathPoint _point) { nodes.push_back(_point); };
	void CreateDefaultPath(sf::Vector2f _thisPostion);
	int GetNextPointID();
};

