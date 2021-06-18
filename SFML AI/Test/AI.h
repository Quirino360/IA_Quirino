#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Flag.h"
#include "SteeringBehavior.h"
#include "StateMachine.h"

namespace gl 
{
	/*
		los estados tienen que estar en el amespce compiladores.
		Semantico, leer que estado es, y guardarlo en analizador lexico
		si es un error, se le manda al error manager al lexico
	*/

	class AI
	{
	public:
		AI();
		AI(sf::Shape* shape);
		AI(sf::Vector2f position);
		AI(sf::Shape* shape, sf::Vector2f position);
		~AI();

		void Init();
		void Update();
		void UpdateSteeringBehavior(sf::Vector2f _targetMovement, sf::Vector2f _targetPosition);
		void Render(sf::RenderWindow* window);
		void Destroy();

		sf::CircleShape AI_CircleShape;

		//Captre the flag
		bool hasFlag = false; // change to true if it has the flag 
		bool canCollition = false;
		sf::Vector2f changeDir = sf::Vector2f(1.0f, 1.0f);

	private:

		StateMachine stateMachine;
		SteeringBehavior sBehavior;

		//Esentials
		unsigned int ID = 0;
		sf::Shape* playerShape = nullptr;
		sf::Texture player_Texture;
		sf::Vector2f playerPosition;

		//steering beahviors
		sf::Vector2f target;
		float maxVelocity = 2;  //before 2
		float maxSpeed = 2;	//before 2
		float maxForce = 2;
		float mass = 1;


	public:

		void CatureTheFlagUpdate(Flag& _flag, std::vector<AI> enemyTeam, bool& allyHasFlag);


		void SteeringBehaviorAIAvoidancePersuitAI(AI _target, std::vector<AI> _obstacles); // Capture the flag
		void SteeringBehaviorAIAvoidancePersuitPlayer(Player _target, std::vector<AI> _obstacles);
		void SteeringBehaviorAIAvoidancePersuitFlag(Flag _target, std::vector<AI> _obstacles); // Capture the flag
		void SteeringBehaviorAIAvoidanceFleeIA(AI _target, std::vector<AI> _obstacles); // Capture the flag

		// ------------------------- Getters ------------------------- //
		sf::Vector2f GetPlayerPosition() { return playerPosition; };
		SteeringBehavior& GetSteeringBehavior() { return sBehavior; };

		// ------------------------- Setters ------------------------- //
		void SetPlayerPosition(sf::Vector2f pos) { playerPosition = pos; };
		void SetMaxVelocity(float _maxVelocity) { maxVelocity = _maxVelocity; };
	private:

		//colition avoidance
		bool lineIntersectsObstacle(sf::Vector2f _ahead, sf::Vector2f _ahead2, sf::CircleShape obstacle); 
		bool lineIntersectsAI(sf::Vector2f _ahead, sf::Vector2f _ahead2, AI obstacle); // Capture the flag
		void findMostThreateningObstacle(sf::Vector2f _ahead, sf::Vector2f _ahead2, std::vector<sf::CircleShape> _obstacles);
		AI findMostThreateningAI(sf::Vector2f _ahead, sf::Vector2f _ahead2, std::vector<AI> _obstacles); // Capture the flag
		bool hasTargetAI = false;
		sf::CircleShape* threadObstacle;

		//AI touched Flag
		AI NearestAI(std::vector<AI> _obstacles);
		bool TouchedFlag(Flag _flag);
	};
}