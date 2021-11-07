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

void SteeringBehavior::UpdateMovement(Actor* _this, Actor* _target, std::vector<Actor*> _other)
{
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
	case BEHAVIOR::FLOCKING:
		SteeringBehaviorFlocking(_this, _other);
		break;
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

void SteeringBehavior::SteeringBehaiviorSeek(Actor* _this, Actor* _target)
{
	steering = Vec2::NormalizeVector(_target->GetPosition() - _this->GetPosition()) * _this->GetForce();
	steering /= _this->GetMass();/**/

	/*
	steering = Vec2::NormalizeVector(_target->GetPosition() - _this->GetPosition());
	steering = Vec2::NormalizeVector(steering - _this->GetVelocity()) * _this->GetForce();
	steering /= _this->GetMass();/**/
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
		timer = 0;
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


// send all the actors that you want inside, even if they aren't
void SteeringBehavior::SteeringBehaviorFlocking(Actor* _this, std::vector<Actor*> _other)
{
	auto& gameObj = GetGameObj();

	float radio = 200;
	sf::Vector2f pos = _this->GetPosition();

	std::vector<Actor*> flockActors;

	// Know what actors are inside
	for (Actor* _actors : _other)
	{
		if (_actors->IsInsidePosition(pos, radio))
		{
			flockActors.push_back(_actors);
		}
	}

	// ----- check if this actor can flock
	bool _continue = false;
	for (Actor* _actors : flockActors)
	{
		if (_actors->GetID() == _this->GetID())
		{
			_continue = true;
		}
	}

	if (flockActors.size() <= 1 || _continue == false)
	{
		steering = { 0,0 };
		return;
	}

	// ----- Alignment
	sf::Vector2f averageVelocity = { 0,0 };
	for (Actor* _actors : flockActors)
	{
		averageVelocity += sf::Vector2f(_actors->GetVelocity().x / flockActors.size(), 
										_actors->GetVelocity().y / flockActors.size());
	}

	averageVelocity = Vec2::NormalizeVector(averageVelocity);
	steering = averageVelocity;

	// ----- Cohesion
	// Aplly a force inside, to the positions average
	sf::Vector2f avergePos = { 0,0 };
	for (Actor* _actors : flockActors)
	{
		if (_this->GetID() != _actors->GetID()) //esto hacerlo en la lista de flock ators
		{
			avergePos += sf::Vector2f(_actors->GetPosition().x / flockActors.size(),
				_actors->GetPosition().y / flockActors.size());
		}
	}

	sf::Vector2f CohecionVelocity = { 0,0 };
	CohecionVelocity = Vec2::NormalizeVector(avergePos - _this->GetPosition());
	steering += CohecionVelocity * 0.2f;
	
	// ----- Separation 
	sf::Vector2f avgPosVec = { 0,0 };
	for (unsigned int j = 0; j < flockActors.size(); j++)
	{
		if (_this->GetID() != flockActors[j]->GetID()) //esto hacerlo en la lista de flock ators
		{
			avgPosVec += sf::Vector2f(flockActors[j]->GetPosition() - _this->GetPosition());
		}
	}

	sf::Vector2f separationVel = { 0,0 };	
	separationVel = Vec2::NormalizeVector(avgPosVec) * 2.5f;
	separationVel *= -1.0f;

	steering += separationVel;
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
