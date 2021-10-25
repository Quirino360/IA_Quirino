#pragma once
#include <SFML/Graphics.hpp>

class Vec2
{
public:
	Vec2();
	~Vec2();

	// ----- MathFunctions 
	static sf::Vector2f NormalizeVector(sf::Vector2f A);
	static sf::Vector2f CrossProduct(sf::Vector2f A, sf::Vector2f B);
	static sf::Vector2f MultiplyVector(sf::Vector2f A, sf::Vector2f B);
	static sf::Vector2f TruncateVector(sf::Vector2f A, float x);

	static float GetAngleDeg(sf::Vector2f A);
	static float GetAngleRad(sf::Vector2f A);
	static float DotProduct(sf::Vector2f A, sf::Vector2f B);
	static float AngleBetweenVectorsDeg(sf::Vector2f A, sf::Vector2f B);
	static float AngleBetweenVectorsRad(sf::Vector2f A, sf::Vector2f B);
	static float DistanceBetweenVectors(sf::Vector2f A, sf::Vector2f B);
	static float VectorLenght(sf::Vector2f A); //magnitude
};

