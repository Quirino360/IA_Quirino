#pragma once
#include "Anim_State.h"

class Anim_StateRun : public Anim_State
{
public:
	Anim_StateRun();
	~Anim_StateRun();

private:

	std::vector<sf::IntRect> animation;

public:
	virtual void Enter(gl::AI _agent);
	virtual ANIMATION_AI_STATE_TYPE Update(gl::AI _agent);
	virtual void Exit(gl::AI _agent);

private:
};

