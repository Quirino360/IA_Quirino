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
		//AI_CircleShape.setRadius(rand() % 20 + 1);
		AI_CircleShape.setRadius(10.0f);
		AI_CircleShape.setOrigin(AI_CircleShape.getRadius() / 2, AI_CircleShape.getRadius() / 2);

		target = sf::Vector2f(rand() % 1060 + 1, rand() % 700 + 1);

		sBehavior = SteeringBehavior(maxVelocity, maxSpeed, maxForce, mass);
		stateMachine = StateMachine(maxVelocity, maxSpeed, maxForce, mass);
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

		sBehavior = SteeringBehavior(maxVelocity, maxSpeed, maxForce, mass);
		stateMachine = StateMachine(maxVelocity, maxSpeed, maxForce, mass);
	}

	AI::AI(sf::Shape* shape, sf::Vector2f position)
	{
	}

	AI::~AI()
	{
	}

	void AI::Init()
	{
		stateMachine.SetCurrentState(STATES::STATE_PERSUIT);
	}

	void AI::Update()
	{
		//playerPosition = playerPosition + sBehavior.GetVelocity();
		
		playerPosition = playerPosition + stateMachine.GetCurentState()->GetVelocity();
		AI_CircleShape.setPosition(playerPosition);
	}

	void AI::UpdateSteeringBehavior(sf::Vector2f _targetMovement, sf::Vector2f _targetPosition)
	{
		stateMachine.Update(playerPosition, _targetMovement, _targetPosition);
		//sBehavior.UpdateMovement(playerPosition, _targetMovement, _targetPosition);
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
		/*if (false == hasFlag && false == allyHasFlag) //if doesnt has the flag, he will follow the flag at all cost
		{
			maxSpeed = 2.0f;
			SteeringBehaviorAIAvoidancePersuitFlag(_flag, enemyTeam);
		}
		else if (false == hasFlag && true == allyHasFlag ) //if his team has the flag he will try to protect him
		{
			maxSpeed = 2.0f;
			//SteeringBehaviorAIAvoidancePersuitAI(NearestAI(enemyTeam), enemyTeam);
			SteeringBehaiviorPersuit(NearestAI(enemyTeam));
		}
		else if (true == hasFlag) // if it has the flag, he will run 
		{
			allyHasFlag = true;
			maxSpeed = 1;
			sf::Vector2f direction = NormalizeVector(velocity);
			sf::Vector2f ahead = AI_CircleShape.getPosition() + NormalizeVector(direction) * 10.0f;
			sf::Vector2f ahead2 = AI_CircleShape.getPosition() + NormalizeVector(direction) * 10.0f / 2.0f;
			_flag.setFlagPosition(playerPosition);
			SteeringBehaiviorFlee(findMostThreateningAI(ahead, ahead2, enemyTeam));
		}/**/
	}




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
		/**/
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
		/**/
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
		/**/
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
		/**/
	}


	bool AI::lineIntersectsObstacle(sf::Vector2f _ahead, sf::Vector2f _ahead2, sf::CircleShape obstacle)
	{
		/*if (DistanceBetweenVectors(obstacle.getPosition(), _ahead) - obstacle.getRadius() <= obstacle.getRadius() || DistanceBetweenVectors(obstacle.getPosition(), _ahead2) - obstacle.getRadius() <= obstacle.getRadius())
			return true;/**/
		return false;
	}

	bool AI::lineIntersectsAI(sf::Vector2f _ahead, sf::Vector2f _ahead2, AI obstacle)
	{
		float avoidanceRadius = 1;
		/*if (DistanceBetweenVectors(obstacle.GetPlayerPosition(), _ahead) - (obstacle.AI_CircleShape.getRadius() + avoidanceRadius) <= obstacle.AI_CircleShape.getRadius() || DistanceBetweenVectors(obstacle.GetPlayerPosition(), _ahead2) - (obstacle.AI_CircleShape.getRadius() + avoidanceRadius) <= obstacle.AI_CircleShape.getRadius())
			return true;/**/
		return false;
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
		}/**/

	}

	AI AI::findMostThreateningAI(sf::Vector2f _ahead, sf::Vector2f _ahead2, std::vector<AI> _obstacles)
	{
		/*
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
		return thread; /**/
		return AI();
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
		return thread;/**/
		return AI();
	}
	bool AI::TouchedFlag(Flag _flag)
	{
		/*
		float avoidanceRadius = 1;
		if (DistanceBetweenVectors(_flag.GetPosition(), playerPosition) - (_flag.GetShape().getRadius() + avoidanceRadius) <= _flag.GetShape().getRadius())
			return true;/**/
		return false;
	}
}