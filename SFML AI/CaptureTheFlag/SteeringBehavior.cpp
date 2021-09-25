#include "SteeringBehavior.h"

#include "Actor.h"
#include "Player.h"
#include "Flag.h"
#include "AI.h"

#include "Vec2.h"
SteeringBehavior::SteeringBehavior()
{
	behavior = BEHAVIOR::IDDLE;
}

SteeringBehavior::~SteeringBehavior()
{
}

void SteeringBehavior::UpdateMovement(Actor* _this, Actor* _target)
{

	if (_this == nullptr || _target == nullptr)
		return;

	if (_this->GetPosition().x == _target->GetPosition().x && _this->GetPosition().y == _target->GetPosition().y)
		_this->SetPosition(_this->GetPosition() + sf::Vector2f(0.01f, 0.01));

	switch (behavior)
	{
	case BEHAVIOR::IDDLE:
		steering = sf::Vector2f(0.0f, 0.0f);
		break;
	case BEHAVIOR::SEEK:
		SteeringBehaiviorSeek(_this, _target);
		break;
	case BEHAVIOR::FLEE:
		SteeringBehaiviorFlee(_this, _target);
		break;
	case BEHAVIOR::ARRIVE:
		SteeringBehaiviorArrival(_this, _target);
		break;
	case BEHAVIOR::PERSUIT:
		SteeringBehaiviorPersuit(_this, _target);
		break;
	case BEHAVIOR::EVADE:
		SteeringBehaiviorEvade(_this, _target);
		break;
	case BEHAVIOR::WANDER:
		SteeringBehaiviorWander(_this);
		break;
	case BEHAVIOR::PATH_FOLLOWING:
		SteeringBehaviorPathFollowing(_this);
		break;
	case BEHAVIOR::COLLITION_AVOIDANCE:
		sf::Vector2f(0.0f, 0.0f);
		break;
	case BEHAVIOR::FLOCKING:
		sf::Vector2f(0.0f, 0.0f);
		break;
	}
	
}

void SteeringBehavior::SteeringBehaiviorSeek(Actor* _this, Actor* _target)
{
	steering = Vec2::NormalizeVector(_target->GetPosition() - _this->GetPosition()) * _this->GetForce();
	steering /= _this->GetMass();
}

void SteeringBehavior::SteeringBehaiviorFlee(Actor* _this, Actor* _target)
{
	steering = -Vec2::NormalizeVector(_target->GetPosition() - _this->GetPosition()) * _this->GetForce();
	steering /= _this->GetMass();
}

void SteeringBehavior::SteeringBehaiviorArrival(Actor* _this, Actor* _target)
{
}

void SteeringBehavior::SteeringBehaiviorWander(Actor* _this)
{
}

void SteeringBehavior::SteeringBehaiviorPersuit(Actor* _this, Actor* _target)
{
	steering = Vec2::NormalizeVector(_target->GetPosition() - (_this->GetPosition() + _this->GetVelocity())) * _this->GetForce();
	steering /= _this->GetMass();
}

void SteeringBehavior::SteeringBehaiviorEvade(Actor* _this, Actor* _target)
{
	steering = Vec2::NormalizeVector(_target->GetPosition() - (_this->GetPosition() + _this->GetVelocity())) * _this->GetForce();
	steering /= _this->GetMass();
}

void SteeringBehavior::SteeringBehaviorPathFollowing(Actor* _this)
{
}

// Path folowing ------------------------- 
void SteeringBehavior::CreateDefaultPath(sf::Vector2f _thisPostion)
{
	float X = 0;
	float Y = 100;
	float radiusAux = 10; //75
	bool aux = false;
	PathPoint pp;

	for (int i = 0; i < 10; i++)
	{
		pp.position = sf::Vector2f(_thisPostion.x + X, _thisPostion.y + Y);
		pp.radius = radiusAux;
		nodes.push_back(pp);

		if (aux)
		{
			Y += 100;
			aux = false;
		}
		else
		{
			X += 100;
			aux = true;
		}
	}

}

void SteeringBehavior::SetPath(std::vector<PathPoint> newPathPoints)
{
}

int SteeringBehavior::GetNextPointID()
{
	if (nodeID >= nodes.size() - 1)
	{
		nodeID = 0;
	}
	else
	{
		nodeID++;
	}
	return nodeID;
}

