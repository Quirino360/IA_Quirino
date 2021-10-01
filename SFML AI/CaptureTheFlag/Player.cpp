#include "Player.h"

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "DeltaTime.h";

#include "Game.h"
#include "Actor.h"

#include <iostream>
#include <cmath>


sf::Clock deltaClock;

Player::Player()
{
}

void Player::Init(sf::Vector2f _position)
{
	Actor::Init(_position);

	SetForce(10);
	sBehavior.SetBehavior(BEHAVIOR::IDDLE);
}

void Player::Update()
{
	Actor::Update();
	Move();
}

void Player::Render(sf::RenderWindow* window)
{
	Actor::Render(window);
	//target doesn't renders
}

void Player::Destroy()
{
	Actor::Destroy();
}

void Player::Move()
{
	float deltaTime = deltaClock.restart().asSeconds();
	auto& gameObj = GetGameObj();
	
	if (IsInsideActor(target) && isSelected == true)
	{

		sBehavior.SetBehavior(BEHAVIOR::IDDLE);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && isSelected == true)
	{
		if (target != nullptr)
		{
			target->Destroy();
			delete target;
			target = nullptr;
		}
		target = new Actor();
		target->Init(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*gameObj.getWindow())));
		sBehavior.SetBehavior(BEHAVIOR::SEEK);
	}

	if (target != nullptr)
		target->Update();

	// ----- 
	sBehavior.UpdateMovement(this, target); // if target is nullptr then it does nothing
	sf::Vector2f steering = sBehavior.GetSteering();
	steering -= velocity;
	velocity += steering;
	position += velocity;

	// ----- 
	velocity += boxCollition.GetCollisionVelocity(gameObj.GetActorManager().GetAllActors(), GetID());
	position += velocity;
}



