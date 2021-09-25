#include "Actor.h"
#include <iostream>
#include "Anim_State.h"
#include "DeltaTime.h";

Actor::Actor()
{
}

Actor::~Actor()
{
}

void Actor::Init(sf::Vector2f _position)
{
	// ----- Esentials
	position = _position;
	cShape.setPosition(position);
	cShape.setRadius(50.0f);
	cShape.setOrigin(cShape.getRadius() / 2, cShape.getRadius() / 2);

	// ----- Texture & Animation
	// ----- Anim State
	AI_AnimState = new ANIMATION_AI_STATE_TYPE;
	*AI_AnimState = ANIMATION_AI_STATE_TYPE::IDLE;

	// ----- Set Texture
	if (texture.loadFromFile("Images/Worm.png"))
		std::cout << "AI Texture Loded" << std::endl;
	cShape.setTexture(&texture);

	// ----- Set Animation //* Crear clase Animation *//
	sf::Vector2u textureSize = texture.getSize();
	textureSize.x /= 12;
	textureSize.y /= 12;
	int x = 0;	int y = 0;	animation.push_back(sf::IntRect(textureSize.x * x, textureSize.y * y, textureSize.x, textureSize.y));
	cShape.setTextureRect(animation[0]);

}

void Actor::Update()
{
	cShape.setPosition(position);
	Animate();
}

void Actor::Render(sf::RenderWindow* window)
{
	window->draw(cShape);
}

void Actor::Destroy()
{
}


void Actor::Animate()
{
	fps += gl::DeltaTime::Time();
	if (fps > 0.5 && animation.size() != 0)
	{
		if (currentFrame >= animation.size())
			currentFrame = 0;
		cShape.setTextureRect(animation[currentFrame]); //animate
		currentFrame++;
		fps = 0;
	}

}