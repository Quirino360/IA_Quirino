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

void Actor::Init(sf::Vector2f _position)
{
	// ----- Essentials
	position = _position;
	cShape.setPosition(position);
	cShape.setRadius(45.0f);
	cShape.setOrigin(cShape.getRadius(), cShape.getRadius());

	// ----- Texture & Animation
	// ----- Anim State
	AI_AnimState = new ANIMATION_AI_STATE_TYPE;
	*AI_AnimState = ANIMATION_AI_STATE_TYPE::IDLE;

	// ----- Set Texture
	//
	if (!texture.loadFromFile("Images/Worm.png")) 	{		
		std::cout << "Texture not Loaded" << std::endl;	}
	cShape.setTexture(&texture);
	texture.getSize();

	// ----- Set Animation //* Crear clase Animation *//
	/*sf::Vector2u textureSize = texture.getSize();
	textureSize.x /= 12;
	textureSize.y /= 12;
	int x = 0;	int y = 0;	animation.push_back(sf::IntRect(textureSize.x * x, textureSize.y * y, textureSize.x, textureSize.y));
	cShape.setTextureRect(animation[0]);/**/

	// Collision box
	boxCollition.Init(_position, { GetRadius() * 2, GetRadius() * 2});

}

void Actor::Update()
{
	auto& gameObj = GetGameObj();
	cShape.setPosition(position);
	Animate();

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

	// Collision box
	boxCollition.Update(position);

	if (collision = true)
	{
		//boxCollition.IsInsideActors(gameObj.);
	}

	

}

void Actor::Render(sf::RenderWindow* window)
{
	window->draw(cShape);

	// Collision box
	boxCollition.Render(window);
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
	if (fps > 0.5 && animation.size() != 0)
	{
		if (currentFrame >= animation.size())
			currentFrame = 0;
		cShape.setTextureRect(animation[currentFrame]); // Animate
		currentFrame++;
		fps = 0;
	}

}