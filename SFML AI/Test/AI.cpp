#include "AI.h"

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "DeltaTime.h";

#include <math.h>   
#include <cmath>

gl::AI::AI()
{
	srand(time(NULL));

	playerCircleShape.setFillColor(sf::Color::Cyan);
	playerPosition = sf::Vector2f(rand() % 1060 + 1, rand() % 700 + 1);
	playerCircleShape.setPosition(playerPosition);
	playerCircleShape.setRadius(rand() % 20 + 1);
	playerCircleShape.setOrigin(playerCircleShape.getRadius() / 2, playerCircleShape.getRadius() / 2);

	target = sf::Vector2f(rand() % 1060 + 1, rand() % 700 + 1);
}

gl::AI::AI(sf::Shape* shape)
{

}

gl::AI::AI(sf::Vector2f position)
{
	playerCircleShape.setFillColor(sf::Color::Cyan);
	playerPosition = position;
	playerCircleShape.setPosition(playerPosition);
	playerCircleShape.setRadius(rand() % 20 + 1); //randon radius bwetween 1 - 20
	playerCircleShape.setOrigin(playerCircleShape.getRadius() / 2, playerCircleShape.getRadius() / 2);

	target = sf::Vector2f(rand() % 1060 + 1, rand() % 700 + 1);

}

gl::AI::AI(sf::Shape* shape, sf::Vector2f position)
{
}

void gl::AI::Init()
{
}

void gl::AI::Update()
{
	playerCircleShape.setPosition(playerPosition);
}

void gl::AI::Render(sf::RenderWindow* window)
{
	window->draw(playerCircleShape);
}

void gl::AI::Destroy()
{
}

void gl::AI::SteeringBehaiviorSeek(sf::Vector2f _target)
{
	sf::Vector2f velocity, desiredVelocity, steering;

	desiredVelocity = NormalizeVector(_target - playerPosition) * maxVelocity;
	steering = desiredVelocity - velocity;
	steering = NormalizeVector(steering) * maxForce;
	steering = steering / mass;
	velocity = NormalizeVector(velocity + steering) * maxSpeed;
	playerPosition = playerPosition + velocity;
}

void gl::AI::SteeringBehaiviorFlee(sf::Vector2f _target)
{
	sf::Vector2f velocity, desiredVelocity, steering;

	desiredVelocity = NormalizeVector(playerPosition - _target) * maxVelocity;
	steering = desiredVelocity - velocity;
	steering = NormalizeVector(steering) * maxForce;
	steering = steering / mass;
	velocity = NormalizeVector(velocity + steering) * maxSpeed;
	playerPosition = playerPosition + velocity;
}

void gl::AI::SteeringBehaiviorArrival(sf::Vector2f _target)
{
	sf::Vector2f velocity, desiredVelocity, steering;
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
}

void gl::AI::SteeringBehaiviorWander()
{
	//sf::Vector2f velocity, desiredVelocity, steering;

	if (rand() % 1000 > 990)
	{
		target = sf::Vector2f(rand() % 1060 + 1, rand() % 700 + 1);
		std::cout << "TargetPos x = " << target.x << " TargetPos y = " << target.y << std::endl;
	}
	SteeringBehaiviorSeek(target);
}

void gl::AI::SteeringBehaiviorPersuit(gl::Player _target)
{

	float distanceDiference = DistanceBetweenVectors( _target.playerCircleShape.getPosition(), playerCircleShape.getPosition());
	float T = distanceDiference / maxVelocity;
	sf::Vector2f futurePosition = _target.playerCircleShape.getPosition() + _target.movement * T;
	SteeringBehaiviorSeek(futurePosition); /**/

	/*float T = 3;
	sf::Vector2f futurePosition = _target.playerCircleShape.getPosition() + _target.movement * T;
	SteeringBehaiviorSeek(futurePosition);/**/
}

void gl::AI::SteeringBehaiviorSeekEvade(gl::Player _target)
{
	float distanceDiference = DistanceBetweenVectors(_target.playerCircleShape.getPosition(), playerCircleShape.getPosition());
	float T = distanceDiference / maxVelocity;
	sf::Vector2f futurePosition = _target.playerCircleShape.getPosition() + _target.movement * T;
	SteeringBehaiviorFlee(futurePosition); /**/
}

sf::Vector2f gl::AI::NormalizeVector(sf::Vector2f A)
{
	float v = std::sqrt((A.x * A.x) + (A.y * A.y));
	return sf::Vector2f(A.x / v, A.y / v);
}

sf::Vector2f gl::AI::TruncateVector(sf::Vector2f A, float x)
{
	return NormalizeVector(A) * x;
}

float gl::AI::DistanceBetweenVectors(sf::Vector2f A, sf::Vector2f B)
{
	float a = A.x - B.x;
	float b = A.y - B.y;
	return std::sqrtf(std::powf(a, 2) + std::powf(b, 2));
}

sf::Vector2f gl::AI::Wander()
{
	return sf::Vector2f();
}


