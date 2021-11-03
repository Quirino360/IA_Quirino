#include "Game.h"
#include "Globals.h"
#include "DeltaTime.h"
#include "Vec2.h"


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
	m_window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Artificial Intelligence");

	// Background Color
	bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
	bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
	bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);

	//View
	view = sf::View(sf::Vector2f(960.0f, 540.0f), sf::Vector2f(1920, 1080));
	m_window->setView(view);

	//imgui 
	ImGui::SFML::Init(*m_window);

	// Background
	_texture.loadFromFile("Images/BackGround.jpg");

	backGround.setSize(static_cast<sf::Vector2f>(m_window->getSize()));
	backGround.setTexture(&_texture);

	// ---------- Actors
	actorManager.CreateActor(ACTOR_TYPE::PLAYER, { 150, 100 });

	actorManager.CreateActor(ACTOR_TYPE::AI, {960, 540});
	/*actorManager.CreateActor(ACTOR_TYPE::AI, { 100, 540 });
	actorManager.CreateActor(ACTOR_TYPE::AI, { 960, 100 });
	actorManager.CreateActor(ACTOR_TYPE::AI, { 500, 250});/**/

	
	actorManager.CreateActor(ACTOR_TYPE::ACTOR, {500, 100});
	actorManager.CreateActor(ACTOR_TYPE::ACTOR, { 150, 500 });
	actorManager.CreateActor(ACTOR_TYPE::ACTOR, { 1000, 750 });
	actorManager.CreateActor(ACTOR_TYPE::ACTOR, { 750, 1000 });
	actorManager.CreateActor(ACTOR_TYPE::ACTOR, { 1500, 500 });/**/

	// Set AI Target
	for (Actor* _actor : actorManager.GetActorsByType(ACTOR_TYPE::AI))
	{
		static_cast<AI*>(_actor)->SetTarget(actorManager.GetActorByID(0));
	}

	// ----- Set Textures
	for (Actor* _actor : actorManager.GetActorsByType(ACTOR_TYPE::ACTOR))
	{
		_actor->SetTexture("Images/Rock.png");/**/
	}
	/*for (Actor* _actor : actorManager.GetActorsByType(ACTOR_TYPE::AI))
	{
		_actor->SetTexture("Images/Orc.png");
	}/**/
	for (Actor* _actor : actorManager.GetActorsByType(ACTOR_TYPE::PLAYER))
	{
		_actor->SetTexture("Images/Link.png");/**/
	}

	// State Machines 
	animStateMachine.Init();
	stateMachine.Init();
}

/*if (showCase01.x > 0)
{
	angle += 90;
}
else if (showCase01.x < 0)
{
	angle -= 90;
}
else if (showCase01.y < 0)
{


}
/**/



void Game::update()
{
	
	for (Actor* _actor : actorManager.GetActorsByType(ACTOR_TYPE::AI))
	{
		stateMachine.Update(static_cast<AI*>(_actor));
		animStateMachine.Update(static_cast<AI*>(_actor));
	}
	actorManager.Update();


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

	m_window->draw(backGround);

	actorManager.Render(m_window);

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
			for (Actor* _actor : actorManager.GetActorsByType(ACTOR_TYPE::AI))
			{
				static_cast<AI*>(_actor)->SetSteeringBehavior(BEHAVIOR::IDDLE);
			}
			
		}
		if (ImGui::Button("SEEK")) {
			for (Actor* _actor : actorManager.GetActorsByType(ACTOR_TYPE::AI))
			{
				static_cast<AI*>(_actor)->SetSteeringBehavior(BEHAVIOR::SEEK);
			}
		}
		if (ImGui::Button("FLEE")) {
			for (Actor* _actor : actorManager.GetActorsByType(ACTOR_TYPE::AI))
			{
				static_cast<AI*>(_actor)->SetSteeringBehavior(BEHAVIOR::FLEE);
			}
		}
		if (ImGui::Button("ARRIVE")) {
			for (Actor* _actor : actorManager.GetActorsByType(ACTOR_TYPE::AI))
			{
				static_cast<AI*>(_actor)->SetSteeringBehavior(BEHAVIOR::ARRIVE);
			}
		}
		if (ImGui::Button("PERSUIT")) {
			for (Actor* _actor : actorManager.GetActorsByType(ACTOR_TYPE::AI))
			{
				static_cast<AI*>(_actor)->SetSteeringBehavior(BEHAVIOR::PERSUIT);
			}
		}
		if (ImGui::Button("EVADE")) {
			for (Actor* _actor : actorManager.GetActorsByType(ACTOR_TYPE::AI))
			{
				static_cast<AI*>(_actor)->SetSteeringBehavior(BEHAVIOR::EVADE);
			}
		}
		if (ImGui::Button("WANDER")) {
			for (Actor* _actor : actorManager.GetActorsByType(ACTOR_TYPE::AI))
			{
				static_cast<AI*>(_actor)->SetSteeringBehavior(BEHAVIOR::WANDER);
			}
		}
		if (ImGui::Button("PATH_FOLLOWING_LOOP")) {
			for (Actor* _actor : actorManager.GetActorsByType(ACTOR_TYPE::AI))
			{
				static_cast<AI*>(_actor)->SetSteeringBehavior(BEHAVIOR::PATH_FOLLOWING_LOOP);
			}
		}
		if (ImGui::Button("PATH_FOLLOWING")) {
			for (Actor* _actor : actorManager.GetActorsByType(ACTOR_TYPE::AI))
			{
				static_cast<AI*>(_actor)->SetSteeringBehavior(BEHAVIOR::PATH_FOLLOWING);
			}
		}
		if (ImGui::Button("PATROL")) {
			for (Actor* _actor : actorManager.GetActorsByType(ACTOR_TYPE::AI))
			{
				static_cast<AI*>(_actor)->SetSteeringBehavior(BEHAVIOR::PATROL);
			}
		}
		if (ImGui::Button("Toggle Show Collision box")) {
			for (Actor* _actor : actorManager.GetActorsByType(ACTOR_TYPE::AI))
			{
				bool show = !_actor->GetDrawCollisionBox();
				_actor->SetDrawCollisionBox(show);
			}
		}
	}
	ImGui::End();
}

Game& GetGameObj()
{
	static Game* game = nullptr;
	if (game == nullptr)
	{
		game = new Game();
	}
	return *game;
}