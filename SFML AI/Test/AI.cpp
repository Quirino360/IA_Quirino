#include "AI.h"

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "DeltaTime.h";

#include "AI_State.h"
#include "Anim_State.h"

#include <math.h>   
#include <cmath>


namespace gl
{
	AI::AI()
	{
		srand(time(NULL));

		position = sf::Vector2f(rand() % 1060 + 1, rand() % 700 + 1);
		AI_CircleShape.setPosition(position);
		AI_CircleShape.setRadius(50.0f);
		AI_CircleShape.setOrigin(AI_CircleShape.getRadius() / 2, AI_CircleShape.getRadius() / 2);
		//AI_CircleShape.setFillColor(sf::Color::Cyan);

	}

	AI::AI(sf::Shape* shape)
	{

	}

	AI::AI(sf::Vector2f _position)
	{
		position = _position;
		AI_CircleShape.setPosition(position);
		AI_CircleShape.setRadius(50.0f);
		AI_CircleShape.setOrigin(AI_CircleShape.getRadius() / 2, AI_CircleShape.getRadius() / 2);
	}

	AI::AI(sf::Shape* shape, sf::Vector2f _position)
	{
	}

	AI::~AI()
	{
	}

	void AI::Init(std::vector<AI>& _allies, std::vector<AI>& _enemies, Flag& _flag, sf::CircleShape& _goal)
	{
		//What To Know
		allies = &_allies;
		enemies = &_enemies;
		flag = &_flag;
		goal = &_goal;

		// Anim State
		AI_AnimState = new ANIMATION_AI_STATE_TYPE;
		*AI_AnimState = ANIMATION_AI_STATE_TYPE::IDLE;

		// Behavior State
		AI_State = new AI_STATE_TYPE;
		*AI_State = AI_STATE_TYPE::CAPTURE_FLAG;

		//Texture & animationon
		if (texture.loadFromFile("Images/Worm.png"))
			std::cout << "AI Texture Loded" << std::endl;
		

		AI_CircleShape.setTexture(&texture);

		sf::Vector2u textureSize = texture.getSize();
		textureSize.x /= 12;
		textureSize.y /= 12;

		int x = 0;	int y = 0;	animation.push_back(sf::IntRect(textureSize.x * x, textureSize.y * y, textureSize.x, textureSize.y));
		
		AI_CircleShape.setTextureRect(animation[0]);

		//Sbehavior
		sBehavior = SteeringBehavior(maxVelocity, maxSpeed, maxForce, mass);

	}

	void AI::Update()
	{
		Animate();
		UpdateFlag();
		direction = NormalizeVector(GetSteeringBehavior().GetVelocity());
	}

	void AI::UpdateSteeringBehavior(sf::Vector2f _targetMovement, sf::Vector2f _targetPosition)
	{
		/*if (IsOnSight())
		{

		}/**/

	}

	void AI::Render(sf::RenderWindow* window)
	{
		window->draw(AI_CircleShape);
	}

	void AI::Destroy()
	{
	}


	float AI::DistanceBetweenVectors(sf::Vector2f A, sf::Vector2f B)
	{
		float a = A.x - B.x;
		float b = A.y - B.y;
		return std::sqrtf(std::powf(a, 2) + std::powf(b, 2));
	}

	

	sf::Vector2f AI::NormalizeVector(sf::Vector2f A)
	{
		float v = std::sqrt((A.x * A.x) + (A.y * A.y));
		return sf::Vector2f(A.x / v, A.y / v);
	}

	bool AI::lineIntersectsAI(sf::Vector2f _ahead, sf::Vector2f _ahead2, AI obstacle)
	{
		float avoidanceRadius = 1;
		if (DistanceBetweenVectors(obstacle.GetPosition(), _ahead) - (obstacle.AI_CircleShape.getRadius() + avoidanceRadius) <= obstacle.AI_CircleShape.getRadius() || DistanceBetweenVectors(obstacle.GetPosition(), _ahead2) - (obstacle.AI_CircleShape.getRadius() + avoidanceRadius) <= obstacle.AI_CircleShape.getRadius())
			return true;
		return false;
	}


	AI AI::findMostThreateningAI(sf::Vector2f _ahead, sf::Vector2f _ahead2)
	{
		hasTargetAI = false;
		AI thread;
		for (int i = 0; i < enemies->size(); i++)
		{
			//is the AI has the flag, then it will collition
			if (lineIntersectsAI(_ahead, _ahead2, (*enemies)[i]) && !hasTargetAI && !hasFlag)
			{
				thread = (*enemies)[i];
				hasTargetAI = true;
			}
			else if (lineIntersectsAI(_ahead, _ahead2, (*enemies)[i]) && DistanceBetweenVectors(AI_CircleShape.getPosition(), (*enemies)[i].GetPosition()) + AI_CircleShape.getRadius() > DistanceBetweenVectors(AI_CircleShape.getPosition(), thread.GetPosition()) + AI_CircleShape.getRadius() && !hasFlag)
			{
				thread = (*enemies)[i];
			}
		}
		return thread; 
		return AI();
	}

	void AI::Animate()
	{
		fps += gl::DeltaTime::Time();
		if (fps > 0.5 && animation.size() != 0)
		{
			if (currentFrame >= animation.size())
				currentFrame = 0;
			AI_CircleShape.setTextureRect(animation[currentFrame]); //animate
			currentFrame++;
			fps = 0;
		}

	}

	float inmunity = 0.0f; //this is so wrong xd
	void AI::UpdateFlag()
	{
		inmunity += gl::DeltaTime::Time();

		if (!hasFlag)
		{
			/*sf::Vector2f ahead = AI_CircleShape.getPosition() + NormalizeVector(velocity) * 10.0f;
			sf::Vector2f ahead2 = AI_CircleShape.getPosition() + NormalizeVector(velocity) * 10.0f / 2.0f;
			target = findMostThreateningAI(ahead, ahead2).position;*/

		}
		if (TouchedFlag() == true && alliesHasFlag == false && inmunity > 8.0f)
		{
			if (hasFlag == false)
			{
				for (gl::AI& ai : *GetAllies())
				{
					ai.hasFlag = false;
					ai.enemyHasFlag = false;
					ai.alliesHasFlag = true;
				}
				for (gl::AI& ai : *GetEnemies())
				{
					ai.hasFlag = false;
					ai.enemyHasFlag = true;
					ai.alliesHasFlag = false;
				}

				hasFlag = true;
			}
			inmunity = 0.0f;
		}
		if (hasFlag == true && TouchedGoal() == true)
		{
			restart = true;
			for (gl::AI& ai : *GetAllies())
			{
				ai.gameResult = 1; // NA = 0, Win = 1, Loose = 2;
			}
			for (gl::AI& ai : *GetEnemies())
			{
				ai.gameResult = 2;// NA = 0, Win = 1, Loose = 2;
			}
		}
		if (hasFlag == true)
		{
			flag->setPosition(this->position);
		}

	}
	bool AI::TouchedFlag()
	{
		if (DistanceBetweenVectors(flag->GetPosition(), position) - (flag->GetShape()->getRadius() ) <= flag->GetShape()->getRadius()) {
			return true;
		}
		return false;
	}
	bool AI::TouchedGoal()
	{
		if (DistanceBetweenVectors(goal->getPosition(), position) - (goal->getRadius()) <= goal->getRadius()) {
			return true;
		}
		return false;
	}
}