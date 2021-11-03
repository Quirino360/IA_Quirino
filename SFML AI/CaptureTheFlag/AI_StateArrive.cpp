#include "AI_StateArrive.h"

AI_StateArrive::AI_StateArrive()
{
	sBehavior = SteeringBehavior();
}

AI_StateArrive::~AI_StateArrive()
{
}

void AI_StateArrive::Enter()
{
	sBehavior.SetBehavior(BEHAVIOR::ARRIVE);
}

AI_STATE_TYPE AI_StateArrive::Update(AI* _agent)
{
	if (_agent->GetSteeringBehavior().GetBehavior() != sBehavior.GetBehavior());
	_agent->GetSteeringBehavior().SetBehavior(sBehavior.GetBehavior());/**/

	//_agent->Update();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num0) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad0))
	{
		return AI_STATE_TYPE::AI_STATE_IDDLE;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad1))
	{
		return AI_STATE_TYPE::AI_STATE_SEEK;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad2))
	{
		return AI_STATE_TYPE::AI_STATE_FLEE;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad4))
	{
		return AI_STATE_TYPE::AI_STATE_PERSUIT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad5))
	{
		return AI_STATE_TYPE::AI_STATE_EVADE;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num6) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad6))
	{
		return AI_STATE_TYPE::AI_STATE_WANDER;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num7) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad7))
	{
		return AI_STATE_TYPE::AI_STATE_PATH_FOLLOWING_LOOP;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num8) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad8))
	{
		return AI_STATE_TYPE::AI_STATE_PATH_FOLLOWING;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num9) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad9))
	{
		return AI_STATE_TYPE::AI_STATE_PATROL;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Dash))
	{
		return AI_STATE_TYPE::AI_STATE_FLOCKING;
	}
	else
	{
		return AI_STATE_TYPE::AI_STATE_ARRIVE;
	}
	//std::cout << "Unexpected Behavior" << std::endl;
}

void AI_StateArrive::Exit()
{
	
}
