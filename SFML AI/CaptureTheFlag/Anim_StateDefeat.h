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
	virtual void Enter(AI* _agent);
	virtual ANIMATION_AI_STATE_TYPE Update(AI* _agent);
	virtual void Exit(AI* _agent);

private:
};

