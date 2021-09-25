#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Actor.h"


class Flag : public Actor
{
public:
	Flag();
	~Flag();

	virtual void Init(sf::Vector2f _position = { 0,0 });
	virtual void Update();
	virtual void Render(sf::RenderWindow* window);
	virtual void Destroy();

	bool DetectIfAITouch(sf::CircleShape _detect, bool _ignore);
private:
	bool isOnPlayer = false;
	
public:

	void ResetFlag();

	// ------------------------- Getters ------------------------- //
	bool GetIsOnPlayer() { return isOnPlayer; };

	// ------------------------- Setters ------------------------- //
	void SetIsOnPlayer(bool TF) { isOnPlayer = TF; };

private:
	float DistanceBetweenVectors(sf::Vector2f A, sf::Vector2f B);
};