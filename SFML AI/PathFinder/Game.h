#pragma once
#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

#include "Tile.h"
#include "Map.h"

class Game
{
public:
	Game() = default;
	~Game() = default;

	void run();
	sf::RenderWindow*& getWindow() { return *&m_window; }


private:
	//sfml
	void init();
	void update();
	void processEvents();
	void render();
	void destroy();

	//imgui
	void UpdateImgui();

private:
	//Esentials
	sf::RenderWindow* m_window;
	sf::View view;

	//Time
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);;
	sf::Clock clock;
	sf::Time timeSinceLastUpdate;

	//Map
	Map mMap;

	//imgui 
	sf::Color bgColor;
	float color[3] = { 0.f, 0.f, 0.f };
	char windowTitle[255] = "ImGui + SFML = <3";
};

