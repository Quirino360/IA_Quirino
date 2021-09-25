#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

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

private:
protected:
	// ----- Esentials
	sf::CircleShape cShape;
	sf::Texture texture;
	ACTOR_TYPE actorType;
	unsigned int ID = 0;

	// ----- Movement
	sf::Vector2f position;
	sf::Vector2f direction;
	sf::Vector2f velocity;
	float force = 1.4f;
	float mass = 1;

	// ----- Animation
	ANIMATION_AI_STATE_TYPE* AI_AnimState;
	std::vector<sf::IntRect> animation;
	unsigned int currentFrame = 0;
	float fps = 0.0f;

public:
	// ---------- Geters
	// ----- Esentials
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

	// ---------- Setters
	// ----- Esentials
	void SetShape(sf::CircleShape _cShape) {  cShape = _cShape; };
	void SetTexture(sf::Texture _texture) {  texture = _texture; };
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

private:
	void Animate();

protected:

};

