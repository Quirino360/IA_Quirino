#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "CollisionBox.h"

enum class ANIMATION_AI_STATE_TYPE;


enum class ACTOR_TYPE
{
	ACTOR = 0,
	PLAYER,
	AI,
	FLAG
};


class Actor
{
public:
	Actor();
	~Actor();
		
	virtual void Init(sf::Vector2f _position = { 0,0 });
	virtual void Update();
	virtual void Render(sf::RenderWindow* window);
	virtual void Destroy();


protected:
	// ----- Essentials
	sf::CircleShape cShape;
	sf::Texture texture;
	ACTOR_TYPE actorType;
	unsigned int ID = 0;

	// ----- Movement
	sf::Vector2f position;
	sf::Vector2f direction;
	sf::Vector2f velocity = {0 , 0} ;
	sf::Vector2f forwardVec;
	float force = 3.0f;
	float mass = 1.2;

	// ----- Animation
	ANIMATION_AI_STATE_TYPE* AI_AnimState;
	std::vector<sf::IntRect> animation;
	unsigned int currentFrame = 0;
	float fps = 0.0f;

	// ----- Select Actor
	bool isSelected = false;

	// ----- Collision Detection
	CollisionBox boxCollition;
	bool collision = true;
	bool showCollisonBox = false;

private:
	// ----- Draw vectors
	sf::RectangleShape directionShape;
	sf::RectangleShape velocityShape;

public:
	// ----- Tools
	bool IsInsidePosition(sf::Vector2f _position, float radius = 0.0f);
	bool IsInsideActor(Actor* _actor);

	// ---------- Getters
	// ----- Essentials
	float GetRadius() { return cShape.getRadius(); };
	sf::CircleShape GetShape() { return cShape; };
	sf::Texture GetTexture() { return texture; };
	ACTOR_TYPE GetActorType() { return actorType; };
	unsigned int GetID() { return ID; };

	// ----- Movement
	sf::Vector2f GetPosition() { return position; };
	sf::Vector2f GetDirection() { return direction; };
	sf::Vector2f GetVelocity() { return velocity; };
	float GetForce() { return force; };
	float GetMass() { return mass; };

	// ----- Animation
	ANIMATION_AI_STATE_TYPE* GetAnimationStateType() { return AI_AnimState; };
	std::vector<sf::IntRect> GetAnimation() { return animation; };

	// ----- Collision detection
	bool GetDrawCollisionBox() { return boxCollition.GetDrawCollisionBox(); };


	// ---------- Setters
	// ----- Essentials
	void SetRadius(float _radius) { cShape.setRadius(_radius); cShape.setOrigin(cShape.getRadius(), cShape.getRadius()); };
	void SetShape(sf::CircleShape _cShape) {  cShape = _cShape; };
	void SetTexture(std::string _path) { if (texture.loadFromFile(_path)) { std::cout << "Texture Loaded" << std::endl; }	cShape.setTexture(&texture); };
	void SetActorType(ACTOR_TYPE _actorType) { actorType = _actorType; };
	void SetID(unsigned int _ID) { ID = _ID; };
	// ----- Movement
	void SetPosition(sf::Vector2f _position) { position = _position; };
	void SetDirection(sf::Vector2f _direction) { direction = _direction; };
	void SetVelocity(sf::Vector2f _velocity) { velocity = _velocity; };
	void SetForce(float _force) { force = _force; };
	void SetMass(float _mass) { mass = _mass; };
	// ----- Animation
	void SetAnimationStateType(ANIMATION_AI_STATE_TYPE* _AI_AnimState) { AI_AnimState = _AI_AnimState; };
	void SetAnimation(std::vector<sf::IntRect> _newAnim) { animation = _newAnim; };
	// ----- Collision detection
	void SetDrawCollisionBox(bool _show) { boxCollition.SetDrawCollisionBox(_show); };

protected:


private:
	void Animate();
};

