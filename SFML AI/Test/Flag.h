#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace gl {

	class Flag
	{
	public:
		Flag();
		Flag(sf::Vector2f position);
		~Flag();

		void Init();
		void Update();
		void Render(sf::RenderWindow* window);
		void Destroy();

		bool DetectIfAITouch(sf::CircleShape _detect, bool _ignore);
	private:
		sf::CircleShape flagShape;
		sf::Vector2f flagPosition;
		bool isOnPlayer = false;
		sf::Texture texture;
		
	public:

		void ResetFlag();

		// ------------------------- Getters ------------------------- //
		sf::Vector2f GetPosition() { return flagPosition; };
		sf::CircleShape* GetShape() { return &flagShape; };
		bool GetIsOnPlayer() { return isOnPlayer; };

		// ------------------------- Setters ------------------------- //
		void setPosition(sf::Vector2f position) { flagPosition = position; };
		void SetIsOnPlayer(bool TF) { isOnPlayer = TF; };

	private:
		float DistanceBetweenVectors(sf::Vector2f A, sf::Vector2f B);
	};

}