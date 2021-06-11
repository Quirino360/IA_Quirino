#include "AI.h"

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "DeltaTime.h";

#include <math.h>   
#include <cmath>

namespace gl
{
	AI::AI()
	{
		srand(time(NULL));

		AI_CircleShape.setFillColor(sf::Color::Cyan);
		playerPosition = sf::Vector2f(rand() % 1060 + 1, rand() % 700 + 1);
		AI_CircleShape.setPosition(playerPosition);
		AI_CircleShape.setRadius(rand() % 20 + 1);
		AI_CircleShape.setOrigin(AI_CircleShape.getRadius() / 2, AI_CircleShape.getRadius() / 2);

		target = sf::Vector2f(rand() % 1060 + 1, rand() % 700 + 1);
	}

	AI::AI(sf::Shape* shape)
	{

	}

	AI::AI(sf::Vector2f position)
	{
		AI_CircleShape.setFillColor(sf::Color::Cyan);
		playerPosition = position;
		AI_CircleShape.setPosition(playerPosition);
		//AI_CircleShape.setRadius(rand() % 20 + 1); //randon radius bwetween 1 - 20
		AI_CircleShape.setRadius(10.0f);
		AI_CircleShape.setOrigin(AI_CircleShape.getRadius() / 2, AI_CircleShape.getRadius() / 2);

		target = sf::Vector2f(rand() % 1060 + 1, rand() % 700 + 1);
	}

	AI::AI(sf::Shape* shape, sf::Vector2f position)
	{
	}

	AI::~AI()
	{
	}

	void AI::Init()
	{
	}

	void AI::Update()
	{
		AI_CircleShape.setPosition(playerPosition);
	}

	void AI::Render(sf::RenderWindow* window)
	{
		window->draw(AI_CircleShape);
	}

	void AI::Destroy()
	{
	}

	void AI::CatureTheFlagUpdate(Flag& _flag, std::vector<AI> enemyTeam, bool& allyHasFlag)
	{
		

		if (false == hasFlag && false == allyHasFlag) //if doesnt has the flag, he will follow the flag at all cost
		{
			maxSpeed = 2.0f;
			SteeringBehaviorAIAvoidancePersuitFlag(_flag, enemyTeam);
		}
		if (false == hasFlag && true == allyHasFlag ) //if his team has the flag he will try to protect him
		{
			maxSpeed = 2.0f;
			//SteeringBehaviorAIAvoidancePersuitAI(NearestAI(enemyTeam), enemyTeam);
			SteeringBehaiviorPersuit(NearestAI(enemyTeam));
		}
		if (true == hasFlag) // if it has the flag, he will run 
		{
			maxSpeed = 1;
			sf::Vector2f direction = NormalizeVector(velocity);
			sf::Vector2f ahead = AI_CircleShape.getPosition() + NormalizeVector(direction) * 10.0f;
			sf::Vector2f ahead2 = AI_CircleShape.getPosition() + NormalizeVector(direction) * 10.0f / 2.0f;
			_flag.setFlagPosition(playerPosition);
			SteeringBehaiviorFlee(findMostThreateningAI(ahead, ahead2, enemyTeam));
		}
	}

	sf::Vector2f AI::SteeringBehaiviorSeek(sf::Vector2f _target)
	{
		desiredVelocity = NormalizeVector(_target - playerPosition) * maxVelocity;
		steering = desiredVelocity - velocity;
		steering = NormalizeVector(steering) * maxForce;
		steering = steering / mass;
		velocity = NormalizeVector(velocity + steering) * maxSpeed;
		playerPosition = playerPosition + velocity;

		return velocity;
	}

	sf::Vector2f AI::SteeringBehaiviorSeek(AI _target)
	{
		desiredVelocity = NormalizeVector(_target.GetPlayerPosition() - playerPosition) * maxVelocity;
		steering = desiredVelocity - velocity;
		steering = NormalizeVector(steering) * maxForce;
		steering = steering / mass;
		velocity = NormalizeVector(velocity + steering) * maxSpeed;
		playerPosition = playerPosition + velocity;

		return velocity;
	}

	sf::Vector2f AI::SteeringBehaiviorFlee(sf::Vector2f _target)
	{
		desiredVelocity = NormalizeVector(playerPosition - _target) * maxVelocity;
		steering = desiredVelocity - velocity;
		steering = NormalizeVector(steering) * maxForce;
		steering = steering / mass;
		velocity = NormalizeVector(velocity + steering) * maxSpeed;
		playerPosition = playerPosition + velocity;
		return velocity;
	}

	sf::Vector2f AI::SteeringBehaiviorFlee(AI _target)
	{
		desiredVelocity = NormalizeVector(playerPosition - _target.GetPlayerPosition()) * maxVelocity;
		steering = desiredVelocity - velocity;
		steering = NormalizeVector(steering) * maxForce;
		steering = steering / mass;
		velocity = NormalizeVector(velocity + steering) * maxSpeed;
		playerPosition = playerPosition + velocity;
		return velocity;
	}

	sf::Vector2f AI::SteeringBehaiviorArrival(sf::Vector2f _target)
	{
		float r = 100;

		if (playerPosition.x <= _target.x + r && playerPosition.x + r >= _target.x && playerPosition.y <= _target.y + r && playerPosition.y + r >= _target.y)//inside
		{
			desiredVelocity = NormalizeVector(_target - playerPosition) * (maxVelocity / 10);
		}
		else
		{
			desiredVelocity = NormalizeVector(_target - playerPosition) * maxVelocity;
		}
		steering = desiredVelocity - velocity;
		velocity = velocity + steering;
		playerPosition = playerPosition + velocity;
		return velocity;
	}

	sf::Vector2f AI::SteeringBehaiviorArrival(AI _target)
	{
		float r = 100;

		if (playerPosition.x <= _target.GetPlayerPosition().x + r && playerPosition.x + r >= _target.GetPlayerPosition().x && playerPosition.y <= _target.GetPlayerPosition().y + r && playerPosition.y + r >= _target.GetPlayerPosition().y)//inside
		{
			desiredVelocity = NormalizeVector(_target.GetPlayerPosition() - playerPosition) * (maxVelocity / 10);
		}
		else
		{
			desiredVelocity = NormalizeVector(_target.GetPlayerPosition() - playerPosition) * maxVelocity;
		}
		steering = desiredVelocity - velocity;
		velocity = velocity + steering;
		playerPosition = playerPosition + velocity;
		return velocity;
	}

	sf::Vector2f AI::SteeringBehaiviorWander()
	{
		if (rand() % 1000 > 990)
		{
			target = sf::Vector2f(rand() % 1060 + 1, rand() % 700 + 1);
			std::cout << "TargetPos x = " << target.x << " TargetPos y = " << target.y << std::endl;
		}
		return SteeringBehaiviorSeek(target);
	}

	sf::Vector2f AI::SteeringBehaiviorPersuit(Player _target)
	{

		float distanceDiference = DistanceBetweenVectors(_target.playerCircleShape.getPosition(), AI_CircleShape.getPosition());
		//distanceDiference -= (_target.playerCircleShape.getRadius() + AI_CircleShape.getRadius());
		float T = distanceDiference / maxVelocity;
		sf::Vector2f futurePosition = _target.playerCircleShape.getPosition() + _target.movement * T;
		return SteeringBehaiviorSeek(futurePosition); /**/
	}

	sf::Vector2f AI::SteeringBehaiviorPersuit(AI _target)
	{
		float distanceDiference = DistanceBetweenVectors(_target.AI_CircleShape.getPosition(), AI_CircleShape.getPosition());
		float T = distanceDiference / maxVelocity;
		sf::Vector2f futurePosition = _target.AI_CircleShape.getPosition() + _target.GetVelocity() * T;
		return SteeringBehaiviorSeek(futurePosition);
	}

	void AI::SteeringBehaiviorEvade(Player _target)
	{
		float distanceDiference = DistanceBetweenVectors(_target.playerCircleShape.getPosition(), AI_CircleShape.getPosition());
		float T = distanceDiference / maxVelocity;
		sf::Vector2f futurePosition = _target.playerCircleShape.getPosition() + _target.movement * T;
		SteeringBehaiviorFlee(futurePosition); /**/
	}

	void AI::SteeringBehaviorPathFollowing()
	{
		if (nodes.size() <= 0)
			CreateDefaultPath();

		pathPointTarget = nodes[nodeID];

		if (DistanceBetweenVectors(playerPosition, pathPointTarget.position) <= pathPointTarget.radius)
		{
			GetNextPointID();
		}

		SteeringBehaiviorSeek(pathPointTarget.position);
	}

	void AI::SteeringBehaviorAIAvoidancePersuitAI(AI _target, std::vector<AI> _obstacles)
	{
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

	//this is the good one
	void AI::SteeringBehaviorAIAvoidancePersuitPlayer(Player _target, std::vector<AI> _obstacles)
	{
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

	sf::Vector2f AI::NormalizeVector(sf::Vector2f A)
	{
		float v = std::sqrt((A.x * A.x) + (A.y * A.y));
		return sf::Vector2f(A.x / v, A.y / v);
	}

	sf::Vector2f AI::TruncateVector(sf::Vector2f A, float x)
	{
		return NormalizeVector(A) * x;
	}

	float AI::DistanceBetweenVectors(sf::Vector2f A, sf::Vector2f B)
	{
		float a = A.x - B.x;
		float b = A.y - B.y;
		return std::sqrtf(std::powf(a, 2) + std::powf(b, 2));
	}

	float AI::VectorLenght(sf::Vector2f A)
	{
		return sqrtf((A.x * A.x) + (A.y * A.y));
	}

	sf::Vector2f AI::Wander()
	{
		return sf::Vector2f();
	}

	void AI::CreateDefaultPath()
	{
		float X = 0;
		float Y = 100;
		float radiusAux = 75;
		bool aux = false;
		PathPoint pp;

		for (int i = 0; i < 10; i++)
		{
			pp.position = sf::Vector2f(playerPosition.x + X, playerPosition.y + Y);
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


	int AI::GetNextPointID()
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

	bool AI::lineIntersectsObstacle(sf::Vector2f _ahead, sf::Vector2f _ahead2, sf::CircleShape obstacle)
	{
		if (DistanceBetweenVectors(obstacle.getPosition(), _ahead) - obstacle.getRadius() <= obstacle.getRadius() || DistanceBetweenVectors(obstacle.getPosition(), _ahead2) - obstacle.getRadius() <= obstacle.getRadius())
			return true;
		return false;
	}

	bool AI::lineIntersectsAI(sf::Vector2f _ahead, sf::Vector2f _ahead2, AI obstacle)
	{
		float avoidanceRadius = 1;
		if (DistanceBetweenVectors(obstacle.GetPlayerPosition(), _ahead) - (obstacle.AI_CircleShape.getRadius() + avoidanceRadius) <= obstacle.AI_CircleShape.getRadius() || DistanceBetweenVectors(obstacle.GetPlayerPosition(), _ahead2) - (obstacle.AI_CircleShape.getRadius() + avoidanceRadius) <= obstacle.AI_CircleShape.getRadius())
			return true;
		return false;
	}

	void AI::findMostThreateningObstacle(sf::Vector2f _ahead, sf::Vector2f _ahead2, std::vector<sf::CircleShape> _obstacles)
	{
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

	AI AI::findMostThreateningAI(sf::Vector2f _ahead, sf::Vector2f _ahead2, std::vector<AI> _obstacles)
	{
		hasTargetAI = false;
		AI thread;
		for (int i = 0; i < _obstacles.size(); i++)
		{
			//is the AI has the flag, then it will collition
			if (lineIntersectsAI(_ahead, _ahead2, _obstacles[i]) && !hasTargetAI && !hasFlag)
			{
				thread = _obstacles[i];
				hasTargetAI = true;
			}
			else if (lineIntersectsAI(_ahead, _ahead2, _obstacles[i]) && DistanceBetweenVectors(AI_CircleShape.getPosition(), _obstacles[i].GetPlayerPosition()) + AI_CircleShape.getRadius() > DistanceBetweenVectors(AI_CircleShape.getPosition(), thread.GetPlayerPosition()) + AI_CircleShape.getRadius() && !hasFlag)
			{
				thread = _obstacles[i];
			}
		}
		return thread;
	}
	AI AI::NearestAI(std::vector<AI> _obstacles)
	{
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
	}
	bool AI::TouchedFlag(Flag _flag)
	{
		float avoidanceRadius = 1;
		if (DistanceBetweenVectors(_flag.GetPosition(), playerPosition) - (_flag.GetShape().getRadius() + avoidanceRadius) <= _flag.GetShape().getRadius())
			return true;
		return false;
	}
}