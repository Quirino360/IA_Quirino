#include "Anim_StateWalkLeft.h"

Anim_StateWalkLeft::Anim_StateWalkLeft()
{
	//Texture & animation
	if (texture.loadFromFile("Images/Worm.png"))
		std::cout << "AI Texture Loded" << std::endl;

	sf::Vector2u textureSize = texture.getSize();
	textureSize.x /= 12;
	textureSize.y /= 12;

	sf::IntRect lel;
	lel.width = 0;
	int x = 7;	int y = 2;	animation.push_back(sf::IntRect(textureSize.x * x, textureSize.y * y, textureSize.x, textureSize.y));
	x = 8;	y = 2;	animation.push_back(sf::IntRect(textureSize.x * x, textureSize.y * y, textureSize.x, textureSize.y));
	x = 9;	y = 2;	animation.push_back(sf::IntRect(textureSize.x * x, textureSize.y * y, textureSize.x, textureSize.y));
}

Anim_StateWalkLeft::~Anim_StateWalkLeft()
{
}

void Anim_StateWalkLeft::Enter(gl::AI& _agent)
{
	_agent.animation = animation;
}

ANIMATION_AI_STATE_TYPE Anim_StateWalkLeft::Update(gl::AI& _agent)
{
	Anim_State::Update(_agent);

	//std::cout << "Walk Left" << std::endl;
	//std::cout << "Dir x = " << _agent.GetDirection().x << " Dir y = " << _agent.GetDirection().y << std::endl;

	float lowestDistance = 100000;
	DIRECTION lowestDir = DIRECTION::NONE;
	for (int i = 0; i < directions.size(); i++) {
		if (SteeringBehavior::DistanceBetweenVectors(directions[i].cord, _agent.GetDirection()) < lowestDistance) {
			lowestDistance = SteeringBehavior::DistanceBetweenVectors(directions[i].cord, _agent.GetDirection());
			lowestDir = directions[i].direction;
		}
	}

	/*// NA = 0, Win = 1, Loose = 2;
	if (_agent.gameResult == 1)
	{
		return ANIMATION_AI_STATE_TYPE::DEFEAT;
	}
	else if (_agent.gameResult == 1)
	{
		return ANIMATION_AI_STATE_TYPE::IDLE; //por ahora iddle
	}/**/

	if (lowestDir == DIRECTION::UP)
	{
		return ANIMATION_AI_STATE_TYPE::WALK_UP;
	}
	else if (lowestDir == DIRECTION::DOWN)
	{
		return ANIMATION_AI_STATE_TYPE::WALK_DOWN;
	}
	else if (lowestDir == DIRECTION::LEFT)
	{
		return ANIMATION_AI_STATE_TYPE::WALK_LEFT;
	}
	else if (lowestDir == DIRECTION::RIGHT)
	{
		return ANIMATION_AI_STATE_TYPE::WALK_RIGHT;
	}
	else if (lowestDir == DIRECTION::NONE)
	{
		return ANIMATION_AI_STATE_TYPE::IDLE;
	}

	return ANIMATION_AI_STATE_TYPE::IDLE;
}

void Anim_StateWalkLeft::Exit(gl::AI& _agent)
{
}
