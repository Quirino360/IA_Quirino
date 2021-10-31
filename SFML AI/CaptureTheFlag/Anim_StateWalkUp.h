#pragma once
#include "Anim_State.h"

class Anim_StateWalkUp : public Anim_State
{
public:
	Anim_StateWalkUp();
	~Anim_StateWalkUp();

	std::vector<sf::IntRect> animation;
	sf::Texture texture;

private:

public:
	virtual void Enter(AI* _agent);
	virtual ANIMATION_AI_STATE_TYPE Update(AI* _agent);
	virtual void Exit(AI* _agent);

private:
};

