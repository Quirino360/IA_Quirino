#pragma once
#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

#include "Actor.h"
#include "Player.h"
#include "Flag.h"
#include "AI.h"

class Game : public Actor
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

	//imgui 
	sf::Color bgColor;
	float color[3] = { 95.0f / 255.f, 35.0f / 255.f, 160.0f / 255.f };
	char windowTitle[255] = "ImGui + SFML = <3";

	// Actors
	Actor* player = new Player;
	Actor* bot = new AI;
};

