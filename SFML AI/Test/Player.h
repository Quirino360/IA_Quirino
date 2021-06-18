#pragma once
#include <SFML/Graphics.hpp>

namespace gl {
	class Player
	{
	public:
		Player();
		Player(sf::Shape* shape);
		Player(sf::Vector2f _position);
		Player(sf::Shape* shape, sf::Vector2f _position);
		~Player() = default;

		void Init();
		void Update();
		void Render(sf::RenderWindow* window);
		void Destroy();


	private:
		sf::CircleShape playerCircleShape;

		unsigned int ID = 0;
		sf::Shape* playerShape = nullptr;
		sf::Texture player_Texture;
		sf::Vector2f movement = sf::Vector2f(1.0f, 1.0f); //this is actualy the direction
		sf::Vector2f position;

		float MaxVelocity = 200;
		float velocity = 200;

		bool hasFlag = false;
		

	public:

		// ------------------------- Getters ------------------------- //
		sf::Vector2f GetMovement() { return movement; };
		sf::Vector2f GetPosition() { return position; };

		// ------------------------- Setters ------------------------- //


	private:

		void Move();
		sf::Vector2f MultiplyVector(sf::Vector2f A, sf::Vector2f B);
	};
}