#include "AI.h"

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include <iostream>

#include "DeltaTime.h";

#include "Game.h"

#include "AI_State.h"

#include "Vec2.h"

#include <math.h>   
#include <cmath>



AI::AI()
{
}

AI::~AI()
{
}

void AI::Init(sf::Vector2f _position)
{
	Actor::Init(_position);
	srand(time(NULL));

	//What To Know UwU

	// Behavior State
	AI_State = new AI_STATE_TYPE;
	*AI_State = AI_STATE_TYPE::AI_STATE_IDDLE;

	// Sbehavior
	sBehavior.SetBehavior(BEHAVIOR::IDDLE);

	// ----- Texture & Animation
	// ----- Anim State
	AI_AnimState = new ANIMATION_AI_STATE_TYPE;
	*AI_AnimState = ANIMATION_AI_STATE_TYPE::IDLE;

	// ----- Set Texture
	//
	if (!texture.loadFromFile("Images/Worm.png")) {
		std::cout << "Texture not Loaded" << std::endl;
	}
	cShape.setTexture(&texture);
	texture.getSize();

	// ----- Set Animation //* Crear clase Animation *//
	sf::Vector2u textureSize = texture.getSize();
	textureSize.x /= 12;
	textureSize.y /= 12;
	int x = 0;	int y = 0;	animation.push_back(sf::IntRect(textureSize.x * x, textureSize.y * y, textureSize.x, textureSize.y));
	cShape.setTextureRect(animation[0]);/**/

}


void AI::Update()
{
	auto& gameObj = GetGameObj();

	Actor::Update();

	// ----- Steering 
	sBehavior.UpdateMovement(this, target);
	sf::Vector2f steering = sBehavior.GetSteering();
	steering = (steering - velocity) * 0.1f;
	velocity += steering;

	// ----- Collision
	velocity += boxCollition.GetCollisionVelocity(gameObj.GetActorManager().GetAllActors(), GetID());
	position += velocity;

	direction = Vec2::NormalizeVector(velocity);

	//std::cout << "velocity = " << velocity.x << " , " << velocity.y << std::endl;
	//std::cout << "box collision velocity " << boxCollition.GetCollisionVelocity(gameObj.GetActorManager().GetAllActors(), GetID()).x << " , " << boxCollition.GetCollisionVelocity(gameObj.GetActorManager().GetAllActors(), GetID()).y << std::endl;
}


void AI::Render(sf::RenderWindow* window)
{
	Actor::Render(window);
	sBehavior.Render(window);
}

void AI::Destroy()
{
	Actor::Destroy();
}

bool AI::lineIntersectsAI(sf::Vector2f _ahead, sf::Vector2f _ahead2, AI obstacle)
{
	float avoidanceRadius = 1;
	if (Vec2::DistanceBetweenVectors(obstacle.GetPosition(), _ahead) - (obstacle.cShape.getRadius() + avoidanceRadius) <= obstacle.cShape.getRadius() || Vec2::DistanceBetweenVectors(obstacle.GetPosition(), _ahead2) - (obstacle.cShape.getRadius() + avoidanceRadius) <= obstacle.cShape.getRadius())
		return true;
	return false;
}


AI AI::findMostThreateningAI(sf::Vector2f _ahead, sf::Vector2f _ahead2)
{
	hasTargetAI = false;
	AI thread;
	for (int i = 0; i < enemies->size(); i++)
	{
		//is the AI has the flag, then it will collision
		if (lineIntersectsAI(_ahead, _ahead2, (*enemies)[i]) && !hasTargetAI && !hasFlag)
		{
			thread = (*enemies)[i];
			hasTargetAI = true;
		}
		else if (lineIntersectsAI(_ahead, _ahead2, (*enemies)[i]) && Vec2::DistanceBetweenVectors(cShape.getPosition(), (*enemies)[i].GetPosition()) + cShape.getRadius() > Vec2::DistanceBetweenVectors(cShape.getPosition(), thread.GetPosition()) + cShape.getRadius() && !hasFlag)
		{
			thread = (*enemies)[i];
		}
	}
	return thread; 
	return AI();
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
			for (AI& ai : *GetAllies())
			{
				ai.hasFlag = false;
				ai.enemyHasFlag = false;
				ai.alliesHasFlag = true;
			}
			for (AI& ai : *GetEnemies())
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
		for (AI& ai : *GetAllies())
		{
			ai.gameResult = 1; // NA = 0, Win = 1, Loose = 2;
		}
		for (AI& ai : *GetEnemies())
		{
			ai.gameResult = 2;// NA = 0, Win = 1, Loose = 2;
		}
	}
	if (hasFlag == true)
	{
		flag->SetPosition(this->position);
	}

}
bool AI::TouchedFlag()
{
	if (Vec2::DistanceBetweenVectors(flag->GetPosition(), position) - (flag->GetShape().getRadius() ) <= flag->GetShape().getRadius()) {
		return true;
	}
	return false;
}
bool AI::TouchedGoal()
{
	if (Vec2::DistanceBetweenVectors(goal->getPosition(), position) - (goal->getRadius()) <= goal->getRadius()) {
		return true;
	}
	return false;
}
