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
	m_window = new sf::RenderWindow(sf::VideoMode(1080, 720), "Artificial Inteligence");

	//center = 540, 360
	sf::Vector2f teamOnePos = sf::Vector2f(440, 360);
	sf::Vector2f teamTwoPos = sf::Vector2f(640, 360);
	for (int i = 0; i < 3; i++)
	{
		if (i == 1)
		{
			teamOnePos = sf::Vector2f(340, 460);
			teamTwoPos = sf::Vector2f(740, 460);
		}
		if (i == 2)
		{
			teamOnePos = sf::Vector2f(340, 260);
			teamTwoPos = sf::Vector2f(740, 260);
		}
		gl::AI teamOneAux = gl::AI(teamOnePos);
		teamOneAux.AI_CircleShape.setFillColor(sf::Color::Green);
		gl::AI teamTwoAux = gl::AI(teamTwoPos);
		teamTwoAux.AI_CircleShape.setFillColor(sf::Color::Red);

		TeamOne.push_back(teamOneAux);
		TeamTwo.push_back(teamTwoAux);
	}
}

void Game::update()
{
	flag.Update();

	for (int i = 0; i < TeamTwo.size(); i++)
	{
		if (TeamOne[i].hasFlag == true)
		{
			teamOneHasTheFlag = true;
		}

		if (TeamTwo[i].hasFlag == true)
		{
			teamTwoHasTheFlag = true;
		}

		if (flag.DetectIfAITouch(TeamOne[i].AI_CircleShape, TeamOne[i].hasFlag) && flag.GetIsOnPlayer())
		{
			flag.ResetFlag();
			TeamTwo[0].hasFlag = false;
			TeamTwo[1].hasFlag = false;
			TeamTwo[2].hasFlag = false;
		}
		if (flag.DetectIfAITouch(TeamOne[i].AI_CircleShape, TeamOne[i].hasFlag) && !flag.GetIsOnPlayer())
		{
			TeamOne[i].hasFlag = true;
			flag.SetIsOnPlayer(true);
		}

		if (flag.DetectIfAITouch(TeamTwo[i].AI_CircleShape, TeamTwo[i].hasFlag) && flag.GetIsOnPlayer())
		{
			flag.ResetFlag();
			TeamOne[0].hasFlag = false;
			TeamOne[1].hasFlag = false;
			TeamOne[2].hasFlag = false;
		}
		if (flag.DetectIfAITouch(TeamTwo[i].AI_CircleShape, TeamTwo[i].hasFlag) && !flag.GetIsOnPlayer())
		{
			TeamTwo[i].hasFlag = true;
			flag.SetIsOnPlayer(true);
		}
	}


	for (int i = 0; i < TeamOne.size(); i++)
	{
		TeamOne[i].Update();
		TeamOne[i].CatureTheFlagUpdate(flag, TeamTwo, teamOneHasTheFlag);
	}
	for (int i = 0; i < TeamTwo.size(); i++)
	{
		TeamTwo[i].Update();
		TeamTwo[i].CatureTheFlagUpdate(flag, TeamOne, teamTwoHasTheFlag);
	}

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

	flag.Render(m_window);

	for (int i = 0; i < TeamOne.size(); i++)
	{
		TeamOne[i].Render(m_window);
	}
	for (int i = 0; i < TeamTwo.size(); i++)
	{
		TeamTwo[i].Render(m_window);
	}

	m_window->display();
}

void Game::destroy()
{
	delete m_window;
}