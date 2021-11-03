#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Actor;

class CollisionBox
{
public:
	CollisionBox() = default;
	~CollisionBox() = default;

	void Init(sf::Vector2f _position = { 0,0 }, sf::Vector2f _size = { 10,10 });
	void Update(sf::Vector2f _position); // Updates position
	void Render(sf::RenderWindow* window);
	void Destroy();

private:
	sf::RectangleShape collisionArea;
	sf::Vector2f upVector;
	sf::Vector2f rightVector;
	sf::Vector2f downVector;
	sf::Vector2f leftVector;

	sf::Vector2f position;

	sf::Vector2f collisionVelocity;
	float force = 40;

	bool drawCollition = false;

public:

	sf::Vector2f  GetCollisionVelocity(Actor* _actor);
	sf::Vector2f  GetCollisionVelocity(std::vector<Actor*> _actors, int exlude = -1);

	// ---------- Getters
	sf::Vector2f GetPosition() { return collisionArea.getPosition(); };
	sf::Vector2f GetSize() { return collisionArea.getSize(); };
	bool GetDrawCollisionBox() { return drawCollition; };

	// ---------- Setters
	void SetDrawCollisionBox(bool _draw) { drawCollition = _draw; };

private:
};

