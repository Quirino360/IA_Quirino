#pragma once
#include <SFML/Graphics.hpp>

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


	private:
		sf::RectangleShape flagShape;
		sf::Vector2f flagPosition;
		bool isOnPlayer = false;

	public:

		void setFlagPosition(sf::Vector2f position);

	};

}