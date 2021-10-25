#include "SteeringBehavior.h"

#include <iostream>
#include "Game.h"

#include "Player.h"
#include "Flag.h"
#include "AI.h"
#include "DeltaTime.h"

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

	/*if (_this->GetPosition().x == _target->GetPosition().x && _this->GetPosition().y == _target->GetPosition().y)
		_this->SetPosition(_this->GetPosition() + sf::Vector2f(0.01f, 0.01));*/

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
	case BEHAVIOR::PATH_FOLLOWING_LOOP:
		SteeringBehaviorPathFollowingLoop(_this);
		break;
	case BEHAVIOR::PATH_FOLLOWING:
		SteeringBehaviorPathFollowing(_this);
		break;
	case BEHAVIOR::PATROL:
		SteeringBehaviorPatrol(_this);
		break;
	case BEHAVIOR::COLLITION_AVOIDANCE:
		sf::Vector2f(0.0f, 0.0f);
		break;
	case BEHAVIOR::FLOCKING:
		sf::Vector2f(0.0f, 0.0f);
		break;
	}

	bool isColDet = true;
	if (isColDet == true)
	{
		CollisionDetection(_this);
	}
	
}

void SteeringBehavior::Render(sf::RenderWindow* window)
{
	// Display path Points
	for (Actor& _actor : pathPoints)
	{
		_actor.Render(window);
	}
	//Display next path point
}

void SteeringBehavior::CollisionDetection(Actor* _this)
{
	sf::Vector2f collisonVel;
	if (_this)
	{

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
	float radius = 500; //Target arrival radius
	steering = Vec2::NormalizeVector(_target->GetPosition() - _this->GetPosition()) * _this->GetForce();
	steering /= _this->GetMass();

	// Inside the target pos + arrival radius
	if (_this->IsInsidePosition(_target->GetPosition(), radius))
	{
		float _distance = Vec2::VectorLenght(_target->GetPosition() - _this->GetPosition());
		float percentage = _distance * 100 / radius; // rule of 3
		std::cout << "percentage = " << percentage << std::endl;
		steering *= percentage / 100;
	}
}

float timer = 0;
void SteeringBehavior::SteeringBehaiviorWander(Actor* _this)
{
	srand(time(NULL));
	auto& gameObj = GetGameObj();

	int _x = gameObj.getWindow()->getSize().x;
	int _y = gameObj.getWindow()->getSize().y;

	timer += gl::DeltaTime::GetDeltaTime();

	// ----- timer y cambiar objetivo
	if (timer >= 5)
	{
		wanderTarget->SetPosition(sf::Vector2f(rand() % _x + 1, rand() % _y + 1)); //rand in range of screen
	}

	// ----- if is inside target change target position
	if (_this->IsInsideActor(wanderTarget))
	{
		wanderTarget->SetPosition(sf::Vector2f(rand() % _x + 1, rand() % _y + 1)); //rand in range of screen
	}

	steering = Vec2::NormalizeVector(wanderTarget->GetPosition() - _this->GetPosition()) * _this->GetForce();
	steering /= _this->GetMass();
}

void SteeringBehavior::SteeringBehaiviorPersuit(Actor* _this, Actor* _target)
{
	steering = Vec2::NormalizeVector(_target->GetPosition() - (_this->GetPosition() + _this->GetVelocity())) * _this->GetForce();
	steering /= _this->GetMass();
}

void SteeringBehavior::SteeringBehaiviorEvade(Actor* _this, Actor* _target)
{
	steering = -Vec2::NormalizeVector(_target->GetPosition() - (_this->GetPosition() + _this->GetVelocity())) * _this->GetForce();
	steering /= _this->GetMass();
}

void SteeringBehavior::SteeringBehaviorPathFollowingLoop(Actor* _this)
{
	//auto& gameObj = GetGameObj();

	if (pathPoints.size() == 0) {
		CreateDefaultPath(_this->GetPosition());
	}

	if (_this->IsInsidePosition(pathPoints[pathID].GetPosition(), pathPoints[pathID].GetRadius())) {
		SetNextPointID(false);
	}

	steering = Vec2::NormalizeVector(pathPoints[pathID].GetPosition() - _this->GetPosition()) * _this->GetForce();
	steering /= _this->GetMass();
}

void SteeringBehavior::SteeringBehaviorPathFollowing(Actor* _this)
{
	//auto& gameObj = GetGameObj();

	if (pathPoints.size() == 0) {
		CreateDefaultPath(_this->GetPosition());
	}

	if (_this->IsInsidePosition(pathPoints[pathID].GetPosition(), pathPoints[pathID].GetRadius()) && pathID != pathPoints.size() - 1) {
		SetNextPointID(false);
	}

	steering = Vec2::NormalizeVector(pathPoints[pathID].GetPosition() - _this->GetPosition()) * _this->GetForce();
	steering /= _this->GetMass();
}

void SteeringBehavior::SteeringBehaviorPatrol(Actor* _this)
{
	auto& gameObj = GetGameObj();

	if (pathPoints.size() == 0) {
		CreateDefaultPath(_this->GetPosition());
	}

	if (_this->IsInsidePosition(pathPoints[pathID].GetPosition(), pathPoints[pathID].GetRadius())) {
		SetNextPointID(true);
	}

	steering = Vec2::NormalizeVector(pathPoints[pathID].GetPosition() - _this->GetPosition()) * _this->GetForce();
	steering /= _this->GetMass();
}

// ---------- Path following  
void SteeringBehavior::CreateDefaultPath(sf::Vector2f _thisPostion)
{
	float X = 0;
	float Y = 150;
	float radiusAux = 10; //75
	bool aux = false;
	Actor pp;

	pp.Init();
	pp.SetPosition(sf::Vector2f(_thisPostion.x, _thisPostion.y));
	pp.SetRadius(radiusAux);
	pp.Update();
	pathPoints.push_back(pp);

	for (int i = 0; i < 9; i++)
	{
		pp.SetPosition(sf::Vector2f(_thisPostion.x + X, _thisPostion.y + Y));
		pp.SetRadius(radiusAux);
		pp.Update();
		pathPoints.push_back(pp);

		if (aux) {
			Y += 150;
			aux = false;
		}
		else {
			X += 200;
			aux = true;
		}
	}

	for (Actor& act : pathPoints)
	{
		//act.SetTexture(sf::Texture NA);
	}

}


bool changeDir = false;
int SteeringBehavior::SetNextPointID(bool _isPatrol)
{
	if (_isPatrol == false)
	{
		if (pathID >= pathPoints.size() - 1) {
			pathID = 0;
		}
		else {
			pathID++;
		}
	}
	else
	{
		if (pathID >= pathPoints.size() - 1) {
			changeDir = true;
		}
		if (pathID <= 0) {
			changeDir = false;
		}

		if (changeDir == false)	{
			pathID++;
		}
		else {
			pathID--;
		}
	}
	return pathID;
}

