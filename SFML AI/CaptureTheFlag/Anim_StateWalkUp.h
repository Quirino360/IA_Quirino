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
	virtual void Enter(gl::AI& _agent);
	virtual ANIMATION_AI_STATE_TYPE Update(gl::AI& _agent);
	virtual void Exit(gl::AI& _agent);

private:
};

