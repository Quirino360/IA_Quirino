#include "Anim_StateDefeat.h"

Anim_StateDefeat::Anim_StateDefeat()
{
	//Texture & animation
	if (texture.loadFromFile("Images/Worm.png"))
		std::cout << "AI Texture Loded" << std::endl;

	sf::Vector2u textureSize = texture.getSize();
	textureSize.x /= 12;
	textureSize.y /= 12;

	sf::IntRect lel;
	lel.width = 0;
	int x = 0;	int y = 5;	animation.push_back(sf::IntRect(textureSize.x * x, textureSize.y * y, textureSize.x, textureSize.y));
	x = 1;	y = 5;	animation.push_back(sf::IntRect(textureSize.x * x, textureSize.y * y, textureSize.x, textureSize.y));
	x = 2;	y = 5;	animation.push_back(sf::IntRect(textureSize.x * x, textureSize.y * y, textureSize.x, textureSize.y));
	x = 3;	y = 5;	animation.push_back(sf::IntRect(textureSize.x * x, textureSize.y * y, textureSize.x, textureSize.y));
	x = 4;	y = 5;	animation.push_back(sf::IntRect(textureSize.x * x, textureSize.y * y, textureSize.x, textureSize.y));
	x = 5;	y = 5;	animation.push_back(sf::IntRect(textureSize.x * x, textureSize.y * y, textureSize.x, textureSize.y));
}

Anim_StateDefeat::~Anim_StateDefeat()
{
}

void Anim_StateDefeat::Enter(AI* _agent)
{
	_agent->SetAnimation(animation);
}

ANIMATION_AI_STATE_TYPE Anim_StateDefeat::Update(AI* _agent)
{
	// NA = 0, Win = 1, Loose = 2;
	if (_agent->gameResult == 0)
	{
		return ANIMATION_AI_STATE_TYPE::IDLE;
	}

	return ANIMATION_AI_STATE_TYPE::IDLE;
}

void Anim_StateDefeat::Exit(AI* _agent)
{
}
