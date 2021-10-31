#pragma once
#include "Anim_State.h"

class Anim_StateDefeat : public Anim_State
{
public:
	Anim_StateDefeat();
	~Anim_StateDefeat();

	std::vector<sf::IntRect> animation;

private:
	sf::Texture texture;

public:
	virtual void Enter(gl::AI* _agent);
	virtual ANIMATION_AI_STATE_TYPE Update(gl::AI* _agent);
	virtual void Exit(gl::AI* _agent);

private:
};

