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

	if (_thisPostion.x == _targetPosition.x && _thisPostion.y == _targetPosition.y)
	{
		_thisPostion.x += 0.01f;
		_thisPostion.y += 0.01f;
	}

	switch (behavior)
	{
	case BEHAVIOR::IDDLE:
		velocity = sf::Vector2f(0.0f, 0.0f);
		sf::Vector2f(0.00001f, 0.00001f);
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
	//steering = desiredVelocity - velocity;
	steering = desiredVelocity;
	if (steering == sf::Vector2f(0, 0)) steering = desiredVelocity - sf::Vector2f(velocity.x/2.0f, velocity.y/2.0f);
		steering = NormalizeVector(steering) * maxForce;

	steering = steering / mass;
	velocity = NormalizeVector(velocity + steering) * maxSpeed;
	//playerPosition = playerPosition + velocity;
	return velocity;

}

sf::Vector2f SteeringBehavior::SteeringBehaiviorFlee(sf::Vector2f _thisPostion, sf::Vector2f _targetPosition)
{
	desiredVelocity = NormalizeVector(_thisPostion - _targetPosition) * maxVelocity;
	//steering = desiredVelocity - velocity;
	steering = desiredVelocity;
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
	return std::sqrtf((A.x * A.x) + (A.y * A.y));
}


// Path folowing ------------------------- 
void SteeringBehavior::CreateDefaultPath(sf::Vector2f _thisPostion)
{
	float X = 0;
	float Y = 100;
	float radiusAux = 10; //75
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

void SteeringBehavior::SetPath(std::vector<PathPoint> newPathPoints)
{
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


/*
void AI::SteeringBehaviorAIAvoidancePersuitAI(AI _target, std::vector<AI> _obstacles)
	{
		/*
		//do persuit
		float AVOIDANCE_FORCE = 10;

		sf::Vector2f velAux = SteeringBehaiviorPersuit(_target);

		//calculate the avoidance vel
		sf::Vector2f direction = NormalizeVector(velocity);
		sf::Vector2f ahead = AI_CircleShape.getPosition() + NormalizeVector(direction) * 10.0f;
		sf::Vector2f ahead2 = AI_CircleShape.getPosition() + NormalizeVector(direction) * 10.0f / 2.0f;

		AI thread = findMostThreateningAI(ahead, ahead2, _obstacles);

		//if there is an obstacle then, do persuit + avoiding force
		if (hasTargetAI)
		{
			sf::Vector2f avoidanceVel = NormalizeVector(ahead - thread.GetPlayerPosition()) * AVOIDANCE_FORCE;

			//do the usual, buth with the persuit velocity extra
			sf::Vector2f finalVel = velAux + avoidanceVel; //persuit and avoidance velocities
			finalVel = TruncateVector(finalVel, maxForce);
			finalVel /= mass;
			velocity = TruncateVector(velocity + finalVel, maxSpeed);
			playerPosition += velocity;
		}
	}

	bool AI::IsOnSight(std::vector<Player> players)
	{
		//calculate the avoidance vel
		/*sf::Vector2f direction = NormalizeVector(velocity);
		float dynamic_length = VectorLenght(velocity) / maxVelocity;
		sf::Vector2f ahead = AI_CircleShape.getPosition() + NormalizeVector(direction) * dynamic_length;

		float avoidanceRadius = 1;
		float onSight = false;

		for (int i = 0; i < players.size(); i++)
		{
			if (DistanceBetweenVectors(players[0].GetPosition(), _ahead) - (obstacle.AI_CircleShape.getRadius() + avoidanceRadius) <= obstacle.AI_CircleShape.getRadius())
		}

		if (DistanceBetweenVectors(obsta.GetPlayerPosition(), _ahead) - (obstacle.AI_CircleShape.getRadius() + avoidanceRadius) <= obstacle.AI_CircleShape.getRadius())

		return onSight;
		return false;
	}

	//this is the good one
	void AI::SteeringBehaviorAIAvoidancePersuitPlayer(Player _target, std::vector<AI> _obstacles)
	{
		/*
		float AVOIDANCE_FORCE = 10;

		//do persuit
		sf::Vector2f velAux = SteeringBehaiviorPersuit(_target);

		//calculate the avoidance vel
		sf::Vector2f direction = NormalizeVector(velocity);
		float dynamic_length = VectorLenght(velocity) / maxVelocity;
		sf::Vector2f ahead = AI_CircleShape.getPosition() + NormalizeVector(direction) * dynamic_length;
		sf::Vector2f ahead2 = AI_CircleShape.getPosition() + NormalizeVector(direction) * dynamic_length / 2.0f;

		AI thread = findMostThreateningAI(ahead, ahead2, _obstacles);

		//if there is an obstacle then, do persuit + avoiding force
		if (hasTargetAI)
		{
			sf::Vector2f avoidanceVel = NormalizeVector(ahead - thread.GetPlayerPosition()) * AVOIDANCE_FORCE;

			//do the usual, buth with the persuit velocity extra
			sf::Vector2f finalVel = velAux + avoidanceVel; //persuit and avoidance velocities
			finalVel = TruncateVector(finalVel, maxForce);
			finalVel /= mass;
			velocity = TruncateVector(velocity + finalVel, maxSpeed);
			playerPosition += velocity;
		}
		
	}

	void AI::SteeringBehaviorAIAvoidancePersuitFlag(Flag _target, std::vector<AI> _obstacles)
	{
		/*
		float AVOIDANCE_FORCE = 10;

		//do persuit
		sf::Vector2f velAux = SteeringBehaiviorSeek(_target.GetPosition());

		//calculate the avoidance vel
		sf::Vector2f direction = NormalizeVector(velocity);
		float dynamic_length = VectorLenght(velocity) / maxVelocity;
		sf::Vector2f ahead = AI_CircleShape.getPosition() + NormalizeVector(direction) * dynamic_length;
		sf::Vector2f ahead2 = AI_CircleShape.getPosition() + NormalizeVector(direction) * dynamic_length / 2.0f;

		AI thread = findMostThreateningAI(ahead, ahead2, _obstacles);

		//if there is an obstacle then, do persuit + avoiding force
		if (hasTargetAI)
		{
			sf::Vector2f avoidanceVel = NormalizeVector(ahead - thread.GetPlayerPosition()) * AVOIDANCE_FORCE;

			//do the usual, buth with the persuit velocity extra
			sf::Vector2f finalVel = velAux + avoidanceVel; //persuit and avoidance velocities
			finalVel = TruncateVector(finalVel, maxForce);
			finalVel /= mass;
			velocity = TruncateVector(velocity + finalVel, maxSpeed);
			playerPosition += velocity;
		}
		
	}

	void AI::SteeringBehaviorAIAvoidanceFleeIA(AI _target, std::vector<AI> _obstacles)
	{
		/*
		float AVOIDANCE_FORCE = 10;

		//do persuit

		sf::Vector2f velAux = SteeringBehaiviorFlee(_target);

		//calculate the avoidance vel
		sf::Vector2f direction = NormalizeVector(velocity);
		float dynamic_length = VectorLenght(velocity) / maxVelocity;
		sf::Vector2f ahead = AI_CircleShape.getPosition() + NormalizeVector(direction) * dynamic_length;
		sf::Vector2f ahead2 = AI_CircleShape.getPosition() + NormalizeVector(direction) * dynamic_length / 2.0f;

		AI thread = findMostThreateningAI(ahead, ahead2, _obstacles);

		//if there is an obstacle then, do persuit + avoiding force
		if (hasTargetAI)
		{
			sf::Vector2f avoidanceVel = NormalizeVector(ahead - thread.GetPlayerPosition()) * AVOIDANCE_FORCE;

			//do the usual, buth with the persuit velocity extra
			sf::Vector2f finalVel = velAux + avoidanceVel; //persuit and avoidance velocities
			finalVel = TruncateVector(finalVel, maxForce);
			finalVel /= mass;
			velocity = TruncateVector(velocity + finalVel, maxSpeed);
			playerPosition += velocity;
		}
		
	}


	void AI::findMostThreateningObstacle(sf::Vector2f _ahead, sf::Vector2f _ahead2, std::vector<sf::CircleShape> _obstacles)
	{
		/*
		//delete to check if there is an obstacle again
		if (threadObstacle != nullptr)
		{
			delete threadObstacle;
			threadObstacle == nullptr;
		}
		for (int i = 0; i < _obstacles.size() - 1; i++)
		{
			if (lineIntersectsObstacle(_ahead, _ahead2, _obstacles[i]) && threadObstacle == nullptr)
			{
				threadObstacle = new sf::CircleShape();
				*threadObstacle = _obstacles[i];
			}
			else if (lineIntersectsObstacle(_ahead, _ahead2, _obstacles[i]) && DistanceBetweenVectors(AI_CircleShape.getPosition(), _obstacles[i].getPosition()) > DistanceBetweenVectors(AI_CircleShape.getPosition(), threadObstacle->getPosition()))
			{
				*threadObstacle = _obstacles[i];
			}
		}

	}

		AI AI::NearestAI(std::vector<AI> _obstacles)
	{
		/*
		float distanceAux= DistanceBetweenVectors(playerPosition, _obstacles[0].playerPosition);
		AI thread = _obstacles[0];

		for (int i = 0; i < _obstacles.size(); i++)
		{
			if (distanceAux < DistanceBetweenVectors(playerPosition, _obstacles[0].playerPosition))
			{
				thread = _obstacles[0];
			}
		}
		return thread;
		return AI();
	}


		bool AI::lineIntersectsObstacle(sf::Vector2f _ahead, sf::Vector2f _ahead2, sf::CircleShape obstacle)
	{
		/*if (DistanceBetweenVectors(obstacle.getPosition(), _ahead) - obstacle.getRadius() <= obstacle.getRadius() || DistanceBetweenVectors(obstacle.getPosition(), _ahead2) - obstacle.getRadius() <= obstacle.getRadius())
			return true;
		return false;
	}

*/