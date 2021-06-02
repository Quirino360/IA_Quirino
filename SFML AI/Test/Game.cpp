#include "Game.h"
#include "Globals.h"


void Game::run()
{
	init();

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (m_window->isOpen())
	{
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
	m_window = new sf::RenderWindow(sf::VideoMode(1080, 720), "SFML Template");	

	gl::DeltaTime::AddTimer("test");
	gl::DeltaTime::SetTimer("test", 2);
	gl::DeltaTime::AddTimer("test2");
	gl::DeltaTime::StopTimer("test2");

	AI_Entity = gl::AI(sf::Vector2f(50.0f, 50.0f));
}

void Game::update()
{

	
	//std::cout << "Mouse,  posX = " << static_cast<sf::Vector2f>(sf::Mouse::getPosition()).x << " PosY = " << static_cast<sf::Vector2f>(sf::Mouse::getPosition()).y << std::endl; //print mouse position x & y 
	//std::cout << "Player,  posX = " << gameManager.GetPlayerByID(0).playerCircleShape.getPosition().x << " PosY = " << gameManager.GetPlayerByID(0).playerCircleShape.getPosition().y << std::endl; //print mouse position x & y 
	player.Update();
	AI_Entity.Update();
	//AI_Entity.SteeringBehaiviorSeek(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*m_window)));
	//AI_Entity.SteeringBehaiviorFlee(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*m_window)));
	//AI_Entity.SteeringBehaiviorArrival(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*m_window)));
	//AI_Entity.SteeringBehaiviorWander();
	//AI_Entity.SteeringBehaiviorPersuit(player);
	//AI_Entity.SteeringBehaiviorSeekEvade(player);
	AI_Entity.SteeringBehaviorPathFollowing();
	/**/
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
	player.Render(m_window);
	AI_Entity.Render(m_window);
	m_window->display();
}

void Game::destroy()
{
	delete m_window;
}