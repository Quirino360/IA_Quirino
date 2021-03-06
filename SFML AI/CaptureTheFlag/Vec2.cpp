#include "Vec2.h"

sf::Vector2f Vec2::NormalizeVector(sf::Vector2f A)
{
	float v = std::sqrt((A.x * A.x) + (A.y * A.y));
	return sf::Vector2f(A.x / v, A.y / v);
}

sf::Vector2f Vec2::MultiplyVector(sf::Vector2f A, sf::Vector2f B)
{
	return sf::Vector2f(A.x * B.x, A.y * B.x);
}


sf::Vector2f Vec2::TruncateVector(sf::Vector2f A, float x)
{
	return NormalizeVector(A) * x;
}

float Vec2::GetAngleDeg(sf::Vector2f A)
{
	return std::atan2f(-A.y, A.x) * (180 / 3.1416);
}

float Vec2::GetAngleRad(sf::Vector2f A)
{
	return std::atan2f(-A.y, A.x);
}

float Vec2::DotProduct(sf::Vector2f A, sf::Vector2f B)
{
	return (A.x * B.x) + (A.y * B.y);
}

float Vec2::AngleBetweenVectorsDeg(sf::Vector2f A, sf::Vector2f B)
{
	return std::acosf(Vec2::DotProduct(Vec2::NormalizeVector(A), Vec2::NormalizeVector(B))) * (180 / 3.1416);
}

float Vec2::AngleBetweenVectorsRad(sf::Vector2f A, sf::Vector2f B)
{
	return std::acosf(Vec2::DotProduct(Vec2::NormalizeVector(A), Vec2::NormalizeVector(B)));	
}

float Vec2::DistanceBetweenVectors(sf::Vector2f A, sf::Vector2f B)
{
	float a = A.x - B.x;
	float b = A.y - B.y;
	return std::sqrtf(std::powf(a, 2) + std::powf(b, 2));
}

float Vec2::VectorLenght(sf::Vector2f A)
{
	return std::sqrtf((A.x * A.x) + (A.y * A.y));
}

