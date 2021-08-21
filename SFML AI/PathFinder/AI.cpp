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

	void AI::Init(sf::Vector2f _position)
	{
		srand(time(NULL));

		position = _position;
		AI_CircleShape.setPosition(position);
		AI_CircleShape.setRadius(15.0f);
		AI_CircleShape.setOrigin(AI_CircleShape.getRadius() / 2, AI_CircleShape.getRadius() / 2);

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
		direction = NormalizeVector(GetSteeringBehavior().GetVelocity());
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
	
}