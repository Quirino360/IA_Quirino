#pragma once
#pragma once
#include <SFML/Graphics.hpp>

#include "AI.h"

#include <vector>

enum class DIRECTION
{
    NONE = -1,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    COUNT
};

struct Direction
{
    Direction() = default;
    Direction(DIRECTION _direction, sf::Vector2f _cord) {
        direction = _direction;
        cord = _cord;
    }
    DIRECTION direction;
    sf::Vector2f cord;
};


enum class ANIMATION_AI_STATE_TYPE
{
    DEFEAT = 0,
    IDLE,
    RUN,
    WALK_UP,
    WALK_DOWN,
    WALK_RIGHT,
    WALK_LEFT
};

class Anim_State
{
public:
    Anim_State();
    Anim_State(std::vector<sf::IntRect> _animation, unsigned int _fps);
    virtual ~Anim_State();

    std::vector<sf::IntRect> animation;
    std::vector<Direction> directions;

private:

    


public:
    virtual void Enter(gl::AI* _agent);
    virtual ANIMATION_AI_STATE_TYPE Update(gl::AI* _agent);
    virtual void Exit(gl::AI* _agent);

private:
};