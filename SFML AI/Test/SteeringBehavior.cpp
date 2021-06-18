#include "SteeringBehavior.h"

SteeringBehavior::SteeringBehavior() : SteeringBehavior(2, 2, 2, 1)
{
}

SteeringBehavior::SteeringBehavior(float _maxVelocity, float _maxSpeed, float _maxForce, float _mass)
{
	behavior = BEHAVIOR::IDDLE;

	maxVelocity = _maxVelocity;
	maxSpeed = _maxSpeed;
	maxForce = _maxForce;
	mass = _mass;
}

SteeringBehavior::~SteeringBehavior()
{
}

void SteeringBehavior::UpdateMovement(sf::Vector2f _thisPostion, sf::Vector2f _targetMovement, sf::Vector2f _targetPosition)
{

	switch (behavior)
	{
	case BEHAVIOR::IDDLE:
		sf::Vector2f(0.0f, 0.0f);
		break;
	case BEHAVIOR::SEEK:
		SteeringBehaiviorSeek(_thisPostion, _targetPosition);
		break;
	case BEHAVIOR::FLEE:
		SteeringBehaiviorFlee(_thisPostion, _targetPosition);
		break;
	case BEHAVIOR::ARRIVE:
		SteeringBehaiviorArrival(_thisPostion, _targetPosition);
		break;
	case BEHAVIOR::PERSUIT:
		SteeringBehaiviorPersuit(_thisPostion, _targetPosition, _targetMovement);
		break;
	case BEHAVIOR::EVADE:
		SteeringBehaiviorEvade(_thisPostion, _targetPosition, _targetMovement);
		break;
	case BEHAVIOR::WANDER:
		SteeringBehaiviorWander(_thisPostion);
		break;
	case BEHAVIOR::PATH_FOLLOWING:
		SteeringBehaviorPathFollowing(_thisPostion);
		break;
	case BEHAVIOR::COLLITION_AVOIDANCE:
		sf::Vector2f(0.0f, 0.0f);
		break;
	case BEHAVIOR::FLOCKING:
		sf::Vector2f(0.0f, 0.0f);
		break;
	}
	
}

sf::Vector2f SteeringBehavior::SteeringBehaiviorSeek(sf::Vector2f _thisPostion, sf::Vector2f _targetPosition)
{
	desiredVelocity = NormalizeVector(_targetPosition - _thisPostion) * maxVelocity;
	steering = desiredVelocity - velocity;
	steering = NormalizeVector(steering) * maxForce;
	steering = steering / mass;
	velocity = NormalizeVector(velocity + steering) * maxSpeed;
	//playerPosition = playerPosition + velocity;
	return velocity;

}

sf::Vector2f SteeringBehavior::SteeringBehaiviorFlee(sf::Vector2f _thisPostion, sf::Vector2f _targetPosition)
{
	desiredVelocity = NormalizeVector(_thisPostion - _targetPosition) * maxVelocity;
	steering = desiredVelocity - velocity;
	steering = NormalizeVector(steering) * maxForce;
	steering = steering / mass;
	velocity = NormalizeVector(velocity + steering) * maxSpeed;
	//playerPosition = playerPosition + velocity;
	return velocity;
}

sf::Vector2f SteeringBehavior::SteeringBehaiviorArrival(sf::Vector2f _thisPostion, sf::Vector2f _targetPosition)
{
	float r = 100;

	if (_thisPostion.x <= _targetPosition.x + r && _thisPostion.x + r >= _targetPosition.x && _thisPostion.y <= _targetPosition.y + r && _thisPostion.y + r >= _targetPosition.y)//inside
	{
		desiredVelocity = NormalizeVector(_targetPosition - _thisPostion) * (maxVelocity / 10);
	}
	else
	{
		desiredVelocity = NormalizeVector(_targetPosition - _thisPostion) * maxVelocity;
	}
	steering = desiredVelocity - velocity;
	velocity = velocity + steering;
	//playerPosition = playerPosition + velocity;
	return velocity;
}

sf::Vector2f SteeringBehavior::SteeringBehaiviorWander(sf::Vector2f _thisPostion)
{
	if (rand() % 1000 > 990)
	{
		pathTarget = sf::Vector2f(rand() % 1060 + 1, rand() % 700 + 1);
		//std::cout << "TargetPos x = " << pathTarget.x << " TargetPos y = " << pathTarget.y << std::endl;
	}
	return SteeringBehaiviorSeek(_thisPostion, pathTarget);
}

sf::Vector2f SteeringBehavior::SteeringBehaiviorPersuit(sf::Vector2f _thisPostion, sf::Vector2f _targetPosition, sf::Vector2f _targetMovement)
{
	float distanceDiference = DistanceBetweenVectors(_targetPosition, _thisPostion);
	//distanceDiference -= (_target.playerCircleShape.getRadius() + AI_CircleShape.getRadius());
	float T = distanceDiference / maxVelocity;
	sf::Vector2f futurePosition = _targetPosition + _targetMovement * T;
	return SteeringBehaiviorSeek(_thisPostion, futurePosition); /**/
}

sf::Vector2f SteeringBehavior::SteeringBehaiviorEvade(sf::Vector2f _thisPostion, sf::Vector2f _targetPosition, sf::Vector2f _targetMovement)
{
	float distanceDiference = DistanceBetweenVectors(_targetPosition, _thisPostion);
	float T = distanceDiference / maxVelocity;
	sf::Vector2f futurePosition = _targetPosition + _targetMovement * T;
	return SteeringBehaiviorFlee(_thisPostion, futurePosition); /**/
}

sf::Vector2f SteeringBehavior::SteeringBehaviorPathFollowing(sf::Vector2f _thisPostion)
{
	if (nodes.size() <= 0)
		CreateDefaultPath(_thisPostion);

	pathPointTarget = nodes[nodeID];

	if (DistanceBetweenVectors(_thisPostion, pathPointTarget.position) <= pathPointTarget.radius)
	{
		GetNextPointID();
	}

	return SteeringBehaiviorSeek(_thisPostion, pathPointTarget.position);
}


// MathFunctions ------------------------- 
sf::Vector2f SteeringBehavior::NormalizeVector(sf::Vector2f A)
{
	float v = std::sqrt((A.x * A.x) + (A.y * A.y));
	return sf::Vector2f(A.x / v, A.y / v);
}

sf::Vector2f SteeringBehavior::TruncateVector(sf::Vector2f A, float x)
{
	return NormalizeVector(A) * x;
}

float SteeringBehavior::DistanceBetweenVectors(sf::Vector2f A, sf::Vector2f B)
{
	float a = A.x - B.x;
	float b = A.y - B.y;
	return std::sqrtf(std::powf(a, 2) + std::powf(b, 2));
}

float SteeringBehavior::VectorLenght(sf::Vector2f A)
{
	return sqrtf((A.x * A.x) + (A.y * A.y));
}


// Path folowing ------------------------- 
void SteeringBehavior::CreateDefaultPath(sf::Vector2f _thisPostion)
{
	float X = 0;
	float Y = 100;
	float radiusAux = 75;
	bool aux = false;
	PathPoint pp;

	for (int i = 0; i < 10; i++)
	{
		pp.position = sf::Vector2f(_thisPostion.x + X, _thisPostion.y + Y);
		pp.radius = radiusAux;

		nodes.push_back(pp);
		if (aux)
		{
			Y += 100;
			aux = false;
		}
		else
		{
			X += 100;
			aux = true;
		}
	}
}

int SteeringBehavior::GetNextPointID()
{
	if (nodeID >= nodes.size() - 1)
	{
		nodeID = 0;
	}
	else
	{
		nodeID++;
	}
	return nodeID;
}
