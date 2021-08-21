#pragma once
#include "Anim_State.h"

class Anim_StateIdle : public Anim_State
{
public:
	Anim_StateIdle();  //an constructur with an new animation to set
	~Anim_StateIdle();

	std::vector<sf::IntRect> animation;
	sf::Texture texture;

private:

public:
	virtual void Enter(gl::AI& _agent);
	virtual ANIMATION_AI_STATE_TYPE Update(gl::AI& _agent);
	virtual void Exit(gl::AI& _agent);

private:
};

