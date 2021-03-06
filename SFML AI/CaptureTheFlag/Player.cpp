#include "Player.h"

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "DeltaTime.h";

#include "Vec2.h"
#include "Game.h"
#include "Actor.h"

#include <iostream>
#include <cmath>

/*

*/

sf::Clock deltaClock;

Player::Player()
{
}

void Player::Init(sf::Vector2f _position, bool setTexture)
{
	Actor::Init(_position);

	playerState = new PLAYER_STATE_TYPE();

	sBehavior.SetBehavior(BEHAVIOR::IDDLE);
}

void Player::Update()
{
	Actor::Update();

	auto& gameObj = GetGameObj();

	// ----- 
	if (IsInsidePosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*gameObj.getWindow()))) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
	{
		isSelected = true;
		cShape.setFillColor(sf::Color::Red);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) &&
		sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) &&
		IsInsidePosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*gameObj.getWindow()))))
	{
		isSelected = false;
		cShape.setFillColor(sf::Color::White);
	}

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
	{
		target->Update();
	}

	// ----- Steering 
	sBehavior.UpdateMovement(this, target);
	sf::Vector2f steering = { 0,0 };
	steering += sBehavior.GetSteering();
	steering = (steering - velocity) * 0.1f;
	velocity += steering;

	// ----- Collision
	if (collision == true)
		velocity += boxCollition.GetCollisionVelocity(gameObj.GetActorManager().GetActorsByType(ACTOR_TYPE::ACTOR), GetID());

	position += velocity;

}
