#include "Actor.h"
#include <iostream>
#include "Anim_State.h"
#include "DeltaTime.h";
#include "Game.h"

#include <iostream>

#include "Vec2.h"

Actor::Actor()
{
}

Actor::~Actor()
{
}

void Actor::Init(sf::Vector2f _position, bool setTexture)
{
	// ----- Essentials
	position = _position;
	cShape.setPosition(position);
	cShape.setRadius(45.0f);
	cShape.setOrigin(cShape.getRadius(), cShape.getRadius());

	// Collision box
	boxCollition.Init(_position, { GetRadius() * 2, GetRadius() * 2});

	// 
	velocityShape.setFillColor(sf::Color::Magenta);

	
}

void Actor::Update()
{
	auto& gameObj = GetGameObj();
	cShape.setPosition(position);
	Animate();

	// Collision box
	if (collision == true)	
		boxCollition.Update(position);


	// ----- Update Vectors shape 
	sf::Vector2f velAux = Vec2::NormalizeVector(velocity);
	velocityShape.setSize({ Vec2::VectorLenght(velAux) * 50, 10 });
	velocityShape.setOrigin(0, velocityShape.getSize().y / 2);
	velocityShape.setPosition(position);
	float angle = Vec2::GetAngleDeg({ velAux.x , -velAux.y });
	velocityShape.setRotation(angle);
}

void Actor::Render(sf::RenderWindow* window)
{
	window->draw(cShape);

	// Collision box
	if (showCollisonBox == true && collision == true)
		boxCollition.Render(window);

	// Vectors Shape
	window->draw(velocityShape);
}

void Actor::Destroy()
{
	// Collision box
	boxCollition.Destroy();
}


bool Actor::IsInsidePosition(sf::Vector2f _position, float _radius)
{
	float _distance = Vec2::VectorLenght(_position - GetPosition()) - (_radius + GetRadius());
	if (_distance < 0 )
	{
		return true;
	}
	return false;
}

bool Actor::IsInsideActor(Actor* _actor)
{
	if (_actor == nullptr)
		return false;

	float _distance = Vec2::VectorLenght(_actor->GetPosition() - GetPosition()) - (_actor->GetRadius() + GetRadius());
	if (_distance <= 0)
	{
		return true;
	}
	return false;
}

void Actor::Animate()
{
	fps += gl::DeltaTime::Time();
	if (fps > 100 && animation.size() != 0)
	{
		if (currentFrame >= animation.size())
			currentFrame = 0;
		cShape.setTextureRect(animation[currentFrame]); // Animate
		currentFrame++;
		fps = 0;
	}

}