#pragma once
#include "Anim_State.h"
class Anim_StateWalkRight :  public Anim_State
{
public:
	Anim_StateWalkRight();
	~Anim_StateWalkRight();

private:

	std::vector<sf::IntRect> animation;
	sf::Texture texture;

public:
	virtual void Enter(AI& _agent);
	virtual ANIMATION_AI_STATE_TYPE Update(AI& _agent);
	virtual void Exit(AI& _agent);

private:
};

