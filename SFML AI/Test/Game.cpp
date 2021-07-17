#include "Game.h"
#include "Globals.h"

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


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
	   // Resolution Centers
	// 1080 * 720 -> 540, 360
	// 2048 * 1080 -> 1024, 540
	// 3840 * 2160 -> 1920, 960
	m_window = new sf::RenderWindow(sf::VideoMode(2048, 1080), "Artificial Inteligence");

	//Set teams 
	/*
	v1 = rand() % 100;         // v1 in the range 0 to 99
	v2 = rand() % 100 + 1;     // v2 in the range 1 to 100
	v3 = rand() % 30 + 1985;   // v3 in the range 1985-2014 */

	sf::Vector2f leftSide = sf::Vector2f(162, 540);
	sf::Vector2f rightSide = sf::Vector2f(1886, 540);

	for (int i = 0; i < 3; i++)
	{
		//left side
		gl::AI teamOneAux = gl::AI(sf::Vector2f(rand() % 920 + 1.0f, rand() % 640 + 460));
		teamOneAux.SetCircleColor(sf::Color::Green);

		//right side
		gl::AI teamTwoAux = gl::AI(sf::Vector2f(rand() % 920 + 1124, rand() % 640 + 460));
		teamTwoAux.SetCircleColor(sf::Color::Red);

		TeamOne.push_back(teamOneAux);
		TeamTwo.push_back(teamTwoAux);
	}

	for (gl::AI &ai : TeamOne)
	{
		ai.Init(TeamOne, TeamTwo, flag, TeamOnegoal);
		ai.SetTarget(flag.GetPosition());
	}
	for (gl::AI &ai : TeamTwo)
	{
		ai.Init(TeamTwo, TeamOne, flag, TeamTwogoal);
		ai.SetTarget(flag.GetPosition());
	}

	//Goals
	TeamOnegoal.setPosition(leftSide);
	TeamOnegoal.setRadius(25);
	TeamOnegoal.setOrigin(TeamOnegoal.getRadius() / 2, TeamOnegoal.getRadius() / 2);
	TeamOnegoal.setFillColor(sf::Color::Green);

	TeamTwogoal.setPosition(rightSide);
	TeamTwogoal.setRadius(25);
	TeamTwogoal.setOrigin(TeamTwogoal.getRadius() / 2, TeamTwogoal.getRadius() / 2);
	TeamTwogoal.setFillColor(sf::Color::Red);

	//StateMachine
	stateMachine.Init();
	animStateMachine.Init();

	//Player
	player = gl::Player(sf::Vector2f(0, 0));
	player.Init();

	//Flag
	flag = gl::Flag(sf::Vector2f(1024, 540));
	flag.Init();

	//Just Testing 
	// 2048 * 1080 -> 1024, 540
	//AI_Entity = gl::AI(sf::Vector2f(rand() % 920 + 1.0f, rand() % 640 + 460)); //left
	//AI_Entity = gl::AI(sf::Vector2f(rand() % 920 + 1124, rand() % 640 + 460)); // right
	//AI_Entity = gl::AI(sf::Vector2f(1024, 0)); // up
	//AI_Entity = gl::AI(sf::Vector2f(1024, 1080)); // up
	//AI_Entity.Init(TeamTwo, TeamOne, flag, TeamTwogoal);
}

void Game::update()
{
	flag.Update();

	for (gl::AI& ai : TeamTwo)
	{
		stateMachine.Update(ai);
		animStateMachine.Update(ai);
		ai.Update();

		if (ai.restart == true)
			restart();
	}
	for (gl::AI& ai : TeamOne)
	{
		stateMachine.Update(ai);
		animStateMachine.Update(ai);
		ai.Update();
		if (ai.restart == true)
			restart();
	}

	player.Update();
	
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

	flag.Render(m_window);

	for (int i = 0; i < TeamOne.size(); i++)
	{
		TeamOne[i].Render(m_window);
	}
	for (int i = 0; i < TeamTwo.size(); i++)
	{
		TeamTwo[i].Render(m_window);
	}

	m_window->draw(TeamOnegoal);
	m_window->draw(TeamTwogoal);

	m_window->display();
}

void Game::destroy()
{
	delete m_window;
}

void Game::restart()
{
	flag.setPosition(sf::Vector2f(1024, 540));

	flag.setPosition(sf::Vector2f(1024, 540));
	for (int i = 0; i < 3; i++)
	{
		TeamOne[i].SetPosition(sf::Vector2f(rand() % 920 + 1.0f, rand() % 640 + 460));
		TeamOne[i].hasFlag = false;
		TeamOne[i].alliesHasFlag = false;
		TeamOne[i].enemyHasFlag = false;
		TeamOne[i].restart = false;

		TeamTwo[i].SetPosition(sf::Vector2f(rand() % 920 + 1124, rand() % 640 + 460));
		TeamTwo[i].hasFlag = false;
		TeamTwo[i].alliesHasFlag = false;
		TeamTwo[i].enemyHasFlag = false;
		TeamTwo[i].restart = false;
	}


}
