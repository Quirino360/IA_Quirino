#pragma once
#include <SFML/Graphics.hpp>
#include "CTexture.h"
#include "Player.h"

namespace gl {
class AI
{
public:
	AI();
	AI(sf::Shape* shape);
	AI(sf::Vector2f position);
	AI(sf::Shape* shape, sf::Vector2f position);
	~AI() = default;

	void Init();
	void Update();
	void Render(sf::RenderWindow * window);
	void Destroy();

	sf::CircleShape playerCircleShape;


private:
	unsigned int ID = 0;
	sf::Shape* playerShape = nullptr;
	sf::Texture player_Texture;

	sf::Vector2f playerPosition;

	//steering beahviors
	sf::Vector2f target;
	float maxVelocity = 2;
	float maxSpeed = 2;
	float maxForce = 2;
	float mass = 1;

public:

	void SteeringBehaiviorSeek(sf::Vector2f _target);
	void SteeringBehaiviorFlee(sf::Vector2f _target);
	void SteeringBehaiviorArrival(sf::Vector2f _target);

	void SteeringBehaiviorWander();
	void SteeringBehaiviorPersuit(gl::Player _target);
	void SteeringBehaiviorSeekEvade(gl::Player _target);


private:
	sf::Vector2f NormalizeVector(sf::Vector2f A);
	sf::Vector2f TruncateVector(sf::Vector2f A, float x);
	float DistanceBetweenVectors(sf::Vector2f A, sf::Vector2f B);
	sf::Vector2f Wander();
};
}


