#include "Game.h"
#include "Globals.h"
#include "DeltaTime.h"

void Game::run()
{
	init();
	m_window->setFramerateLimit(120);

	timeSinceLastUpdate = sf::Time::Zero;
	while (m_window->isOpen())
	{
		timeSinceLastUpdate += clock.restart();
		processEvents();

		gl::DeltaTime::Update(timeSinceLastUpdate.asSeconds());
		UpdateImgui();
		update();
		gl::Input::Update();

		render();
	}

	destroy();
}

void Game::init()
{
	//window center = 960 , 540
	m_window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Artificial Inteligence");

	// Background Color
	bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
	bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
	bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);

	//View
	view = sf::View(sf::Vector2f(960.0f, 540.0f), sf::Vector2f(1920, 1080));
	m_window->setView(view);

	//imgui 
	ImGui::SFML::Init(*m_window);

	// Actors
	player->Init();
	bot->Init();

	static_cast<AI*>(bot)->SetTarget(player);
}

void Game::update()
{
	player->Update();
	bot->Update();
}

void Game::processEvents()
{
	sf::Event event;
	while (m_window->pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(event);
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			gl::Input::HandleInputs(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			gl::Input::HandleInputs(event.key.code, false);
			break;
		case sf::Event::Closed:
			m_window->close();
			break;
		}
	}
}

void Game::render()
{
	m_window->clear(bgColor); // fill background with color

	player->Render(m_window);
	bot->Render(m_window);

	ImGui::SFML::Render(*m_window); //render imgui
	m_window->display();
}

void Game::destroy()
{
	delete m_window;
	ImGui::SFML::Shutdown();
}



void Game::UpdateImgui()
{
	ImGui::SFML::Update(*m_window, clock.getElapsedTime());

	if (ImGui::Begin("Control Panel")) // begin window
	{
		if (ImGui::ColorEdit3("Background color", color)) {
			// this code gets called if color value changes, so
			// the background color is upgraded automatically!
			bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
			bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
			bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);
		}

		if (ImGui::Button("IDDLE")) {
			
		}
		if (ImGui::Button("SEEK")) {

		}
		if (ImGui::Button("FLEE")) {

		}
		if (ImGui::Button("ARRIVE")) {

		}
		if (ImGui::Button("PERSUIT")) {

		}
		if (ImGui::Button("EVADE")) {

		}
		if (ImGui::Button("WANDER")) {

		}
		if (ImGui::Button("PATH_FOLLOWING")) {

		}
		if (ImGui::Button("COLLITION_AVOIDANCE")) {

		}
	}
	ImGui::End();
}
