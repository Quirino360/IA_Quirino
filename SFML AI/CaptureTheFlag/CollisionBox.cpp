#include "CollisionBox.h"

#include <iostream>

#include "Game.h"


#include "Actor.h"
#include "Vec2.h"

void CollisionBox::Init(sf::Vector2f _position, sf::Vector2f _size)
{
	collisionArea.setSize(_size);
	collisionArea.setOrigin(_size.x / 2, _size.y / 2);
	collisionArea.setPosition(_position);
}

// Updates the position of the collision box
void CollisionBox::Update(sf::Vector2f _position)
{
	collisionArea.setPosition(_position);
}

void CollisionBox::Render(sf::RenderWindow* window)
{
	auto& gameObj = GetGameObj();

	if (drawCollition == true)	{
		window->draw(collisionArea);
	}
}

void CollisionBox::Destroy()
{
}


sf::Vector2f CollisionBox::GetCollisionVelocity(Actor* _target)
{
	// Optimizations, obstacle(s) closer o obstacle st range
	// Set corners Positions
	sf::Vector2f topLeftCorner = { GetPosition().x - GetSize().x / 2, GetPosition().y - GetSize().y / 2 };
	sf::Vector2f topRightCorner = { GetPosition().x + GetSize().x / 2, GetPosition().y - GetSize().y / 2 };
	sf::Vector2f bottomRightCorner = { GetPosition().x + GetSize().x / 2, GetPosition().y + GetSize().y / 2 };
	sf::Vector2f bottomLeftCorner = { GetPosition().x - GetSize().x / 2, GetPosition().y + GetSize().y / 2 };

	// Set Corners to Target Vectors
	sf::Vector2f topLeftToTarget = _target->GetPosition() - topLeftCorner;
	sf::Vector2f topRightToTarget = _target->GetPosition() - topRightCorner;
	sf::Vector2f bottomRightToTarget = _target->GetPosition() - bottomRightCorner;
	sf::Vector2f bottomLeftToTarget = _target->GetPosition() - bottomLeftCorner;

	// Set Vertex Vectors
	upVector = Vec2::NormalizeVector(topRightCorner - topLeftCorner);
	rightVector = Vec2::NormalizeVector(bottomRightCorner - topRightCorner);
	downVector = Vec2::NormalizeVector( bottomLeftCorner - bottomRightCorner);
	leftVector = Vec2::NormalizeVector(topLeftCorner - bottomLeftCorner);

	// Projections Vectors
	sf::Vector2f upVectorProyection = upVector * Vec2::DotProduct (upVector, topLeftToTarget);
	sf::Vector2f rightVectorProyection = rightVector * Vec2::DotProduct(rightVector, topRightToTarget);
	sf::Vector2f downVectorProyection = downVector * Vec2::DotProduct(downVector, bottomRightToTarget);
	sf::Vector2f leftVectorProyection = leftVector * Vec2::DotProduct(leftVector, bottomLeftToTarget);

	// ---------- Detect Collision
	sf::Vector2f _collisionVelocity = { 0,0 };
	// ----- Projection collision
	if (Vec2::VectorLenght(upVectorProyection - topLeftToTarget) <= _target->GetRadius() &&
		Vec2::VectorLenght(upVectorProyection) < Vec2::VectorLenght(topRightCorner - topLeftCorner) &&
		Vec2::VectorLenght(upVectorProyection) > 0)
	{
		//_collisionVelocity += Vec2::NormalizeVector({ 0,1 }) * force;
		collisionVelocity += Vec2::NormalizeVector(upVectorProyection - topLeftToTarget) * force;
	}
	else if (Vec2::VectorLenght(rightVectorProyection - topRightToTarget) <= _target->GetRadius() &&
		Vec2::VectorLenght(rightVectorProyection) < Vec2::VectorLenght(bottomRightCorner - topRightCorner) &&
		Vec2::VectorLenght(rightVectorProyection) > 0)
	{
		//_collisionVelocity += Vec2::NormalizeVector({ -1,0 }) * force;
		collisionVelocity += Vec2::NormalizeVector(rightVectorProyection - topRightToTarget) * force;
	}
	else if (Vec2::VectorLenght(downVectorProyection - bottomRightToTarget) <= _target->GetRadius() &&
		Vec2::VectorLenght(downVectorProyection) < Vec2::VectorLenght(bottomLeftCorner - bottomRightCorner) &&
		Vec2::VectorLenght(downVectorProyection) > 0)
	{
		//_collisionVelocity += Vec2::NormalizeVector({ 0,-1 }) * force;
		collisionVelocity += Vec2::NormalizeVector(downVectorProyection - bottomRightToTarget) * force;
	}
	else if (Vec2::VectorLenght(leftVectorProyection - bottomLeftToTarget) <= _target->GetRadius() &&
		Vec2::VectorLenght(leftVectorProyection) < Vec2::VectorLenght(topLeftCorner - bottomLeftCorner) &&
		Vec2::VectorLenght(leftVectorProyection) > 0)
	{
		//_collisionVelocity += Vec2::NormalizeVector({ 1,0 }) * force;
		collisionVelocity += Vec2::NormalizeVector(leftVectorProyection - bottomLeftToTarget) * _target->GetCollisonForce();
	}
	// ----- Corners collision
	else if (_target->IsInsidePosition(topLeftCorner))
	{
		_collisionVelocity += Vec2::NormalizeVector(topLeftCorner - _target->GetPosition()) * _target->GetCollisonForce();
	}
	else if (_target->IsInsidePosition(topRightCorner))
	{
		_collisionVelocity += Vec2::NormalizeVector(topRightCorner - _target->GetPosition()) * _target->GetCollisonForce();
	}
	else if (_target->IsInsidePosition(bottomLeftCorner))
	{
		_collisionVelocity += Vec2::NormalizeVector(bottomLeftCorner - _target->GetPosition()) * _target->GetCollisonForce();
	}
	else if (_target->IsInsidePosition(bottomRightCorner))
	{
		_collisionVelocity += Vec2::NormalizeVector(bottomRightCorner - _target->GetPosition()) * _target->GetCollisonForce();
	}

	return _collisionVelocity;
}

sf::Vector2f CollisionBox::GetCollisionVelocity(std::vector<Actor*> _actors, int exlude)
{
	collisionVelocity = { 0,0 };
	for (Actor* _actor : _actors)
	{
		if (_actor->GetID() != exlude)
		{
			collisionVelocity += GetCollisionVelocity(_actor);
		}
	}
	return collisionVelocity;
}
