#include "CollitionDetection.h"

gl::CollitionDetection::CollitionDetection()
{
}

gl::CollitionDetection::~CollitionDetection()
{
}



bool gl::CollitionDetection::DetectCollision(sf::Shape* _other)
{
	return false;
}

sf::Vector2f gl::CollitionDetection::TargetDistance(sf::Shape* _other)
{
	return sf::Vector2f();
}

void gl::CollitionDetection::AddCircleCollision()
{
}

void gl::CollitionDetection::AddCircleCollision(sf::Vector2f _size)
{
}

void gl::CollitionDetection::setRectangleSize(float r)
{
}

void gl::CollitionDetection::setCircleRadius(float r)
{
}

void gl::CollitionDetection::AddRectangleCollision()
{
}

void gl::CollitionDetection::AddRectangleCollision(sf::Vector2f _size)
{
}
