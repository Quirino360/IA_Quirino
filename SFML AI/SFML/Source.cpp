#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1080, 720), "SFML", sf::Style::Resize | sf::Style::Close);
	sf::RectangleShape player(sf::Vector2f(100.0f, 100.0f));
	player.setFillColor(sf::Color::Cyan);

	while (window.isOpen())
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::Resized:
				printf("New window width %i & height %i\n", evnt.size.width, evnt.size.height);
				break;

			case sf::Event::TextEntered:
				if (evnt.text.unicode < 128)
				{
					printf("%c", evnt.text.unicode);
				}
			}
		}

		window.draw(player);
		window.display();
	}
}