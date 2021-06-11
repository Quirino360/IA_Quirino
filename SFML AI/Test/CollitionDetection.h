#pragma once
#include <SFML/Graphics.hpp>

namespace gl {
	class CollitionDetection
	{
	public:
		CollitionDetection();
		~CollitionDetection();


	private:
		sf::CircleShape CircleCollision;
		sf::RectangleShape SquareCollision;

		float radiusToDetectOthers = 500.0f;

		bool hasCircle = false;
		bool hasRectangle = false;
		bool isTrigger = false; //true can enter & true'nt can't enter

	public:
		bool DetectCollision(sf::Shape* _other);
		sf::Vector2f TargetDistance(sf::Shape* _other);

		void AddCircleCollision();
		void AddCircleCollision(sf::Vector2f _size);
		void setCircleRadius(float r);

		void AddRectangleCollision();
		void AddRectangleCollision(sf::Vector2f _size);
		void setRectangleSize(float r);

	private:
	};
}