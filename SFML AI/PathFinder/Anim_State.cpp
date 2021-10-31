#include "Anim_State.h"
#include "DeltaTime.h"

Anim_State::Anim_State()
{
    sf::Vector2f UP = sf::Vector2f(0.0f, -1.0f);
    sf::Vector2f DOWN = sf::Vector2f(0.0f, 1.0f);
    sf::Vector2f LEFT = sf::Vector2f(-1.0f, 0.0f);
    sf::Vector2f RIGHT = sf::Vector2f(1.0f, 0.0f); 

    directions.push_back(Direction(DIRECTION::UP, UP));
    directions.push_back(Direction(DIRECTION::DOWN, DOWN));
    directions.push_back(Direction(DIRECTION::LEFT, LEFT));
    directions.push_back(Direction(DIRECTION::RIGHT, RIGHT));
}

Anim_State::Anim_State(std::vector<sf::IntRect> _animation, unsigned int _fps)
{
}

Anim_State::~Anim_State()
{
}

void Anim_State::Enter(gl::AI* _agent)
{
}

ANIMATION_AI_STATE_TYPE Anim_State::Update(gl::AI* _agent)
{
    return ANIMATION_AI_STATE_TYPE();
}

void Anim_State::Exit(gl::AI* _agent)
{
}
