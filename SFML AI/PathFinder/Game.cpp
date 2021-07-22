#include "Game.h"
#include "Globals.h"

void Game::run()
{
	init();

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	//imgui 
	sf::Color bgColor;
	float color[3] = { 0.f, 0.f, 0.f };
	char windowTitle[255] = "ImGui + SFML = <3";

	sf::Clock deltaClock;
	while (m_window->isOpen())
	{
		//imgui 
		sf::Event event;
		while (m_window->pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed)
			{
				m_window->close();
			}
		}

		ImGui::SFML::Update(*m_window, deltaClock.restart());
		ImGui::Begin("Sample window"); // begin window

		// Background color edit
		if (ImGui::ColorEdit3("Background color", color))
		{
			bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
			bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
			bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);
		}

		// Window title text edit
		ImGui::InputText("Window title", windowTitle, 255);

		if (ImGui::Button("Update window title"))
		{
			m_window->setTitle(windowTitle);
		}

		ImGui::End(); // end window

		m_window->clear(bgColor); // fill background with color
		ImGui::SFML::Render(*m_window);
		m_window->display();


		//sfml
		processEvents();

		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate >= timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			gl::DeltaTime::Update(timePerFrame.asSeconds());
			update();
			gl::Input::Update();
		}
		render();
	}

	destroy();
}

void Game::init()
{
	//window
	m_window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "SFML Template");

	//imgui 
	ImGui::SFML::Init(*m_window);

	//


	m_shape.setFillColor(sf::Color::Red);
	m_shape.setPosition({100, 100});
	m_shape.setRadius(25);

	gl::DeltaTime::AddTimer("test");
	gl::DeltaTime::SetTimer("test", 2);
	gl::DeltaTime::AddTimer("test2");
	gl::DeltaTime::StopTimer("test2");
}

void Game::update()
{
	
}

void Game::processEvents()
{
	sf::Event event;
	while (m_window->pollEvent(event))
	{
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
	m_window->clear();
	m_window->draw(m_shape);


	m_window->display();
}

void Game::destroy()
{
	delete m_window;
	ImGui::SFML::Shutdown();
}