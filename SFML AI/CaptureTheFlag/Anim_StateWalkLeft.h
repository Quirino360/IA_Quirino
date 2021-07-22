#pragma once
#include "Anim_State.h"
class Anim_StateWalkLeft :  public Anim_State
{
public:
	Anim_StateWalkLeft();
	~Anim_StateWalkLeft();

private:

	std::vector<sf::IntRect> animation;
	sf::Texture texture;

public:
	virtual void Enter(gl::AI& _agent);
	virtual ANIMATION_AI_STATE_TYPE Update(gl::AI& _agent);
	virtual void Exit(gl::AI& _agent);

private:
};

