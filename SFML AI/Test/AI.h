#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Flag.h"

namespace gl 
{
	/*
	* los estados tienen que estar en el amespce compiladores.
		Semantico, leer que estado es, y guardarlo en analizador lexico
		si es un error, se le manda al error manager al lexico
	*/
	struct PathPoint
	{
		sf::Vector2f position;
		float radius;
	};

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
		void Render(sf::RenderWindow* window);
		void Destroy();

		sf::CircleShape AI_CircleShape;

		//Captre the flag
		bool hasFlag = false; // change to true if it has the flag 
		bool canCollition = false;
		sf::Vector2f changeDir = sf::Vector2f(1.0f, 1.0f);

	private:
		//Esentials
		unsigned int ID = 0;
		sf::Shape* playerShape = nullptr;
		sf::Texture player_Texture;
		sf::Vector2f playerPosition;

		//steering beahviors
		sf::Vector2f velocity, desiredVelocity, steering; //used in seek, flee
		sf::Vector2f target;
		float maxVelocity = 2;  //before 2
		float maxSpeed = 2;	//before 2
		float maxForce = 2;
		float mass = 1;


	public:

		void CatureTheFlagUpdate(Flag& _flag, std::vector<AI> enemyTeam, bool& allyHasFlag);
		/*
		Seek ---------- DONE
		Flee ---------- DONE
		Arrive ---------- DONE
		Pursuit ---------- DONE
		Evade ---------- DONE
		Wander ---------- TO_UPGRADE
		Path Following ---------- DONE
		Collition Avoidance ---------- TO UPGRADE
		Flocking ---------- TO_DO

		Capture the flag ---------- TO_DO
		/**/
		sf::Vector2f SteeringBehaiviorSeek(sf::Vector2f _target);
		sf::Vector2f SteeringBehaiviorSeek(AI _target);

		sf::Vector2f SteeringBehaiviorFlee(sf::Vector2f _target);
		sf::Vector2f SteeringBehaiviorFlee(AI _target); // Capture the flag

		sf::Vector2f SteeringBehaiviorArrival(sf::Vector2f _target);
		sf::Vector2f SteeringBehaiviorArrival(AI _target);

		sf::Vector2f SteeringBehaiviorWander(); //Mejorar collition y la manera de hacerlo

		sf::Vector2f SteeringBehaiviorPersuit(Player _target);
		sf::Vector2f SteeringBehaiviorPersuit(AI _target);

		void SteeringBehaiviorEvade(Player _target);

		void SteeringBehaviorPathFollowing();

		void SteeringBehaviorAIAvoidancePersuitAI(AI _target, std::vector<AI> _obstacles); // Capture the flag
		void SteeringBehaviorAIAvoidancePersuitPlayer(Player _target, std::vector<AI> _obstacles);
		void SteeringBehaviorAIAvoidancePersuitFlag(Flag _target, std::vector<AI> _obstacles); // Capture the flag
		
		void SteeringBehaviorAIAvoidanceFleeIA(AI _target, std::vector<AI> _obstacles); // Capture the flag

		void SteeringBehaviorFlocking();


		// ------------------------- Getters ------------------------- //
		sf::Vector2f GetPlayerPosition() { return playerPosition; };
		sf::Vector2f GetVelocity() { return velocity; };

		// ------------------------- Setters ------------------------- //
		void SetPlayerPosition(sf::Vector2f pos) { playerPosition = pos; };
		void SetVelocity(sf::Vector2f _velocity) { velocity = _velocity; };
		void SetMaxVelocity(float _maxVelocity) { maxVelocity = _maxVelocity; };
	private:
		//esentials
		sf::Vector2f NormalizeVector(sf::Vector2f A);
		sf::Vector2f TruncateVector(sf::Vector2f A, float x);
		float DistanceBetweenVectors(sf::Vector2f A, sf::Vector2f B);
		float VectorLenght(sf::Vector2f A); //magnitude

		//wander
		sf::Vector2f Wander();

		//path folowing
		std::vector<PathPoint> nodes;
		int nodeID = 0;
		PathPoint pathPointTarget;
		void CreateDefaultPath();
		void AddPathPoint(PathPoint _point) { nodes.push_back(_point); };
		int GetNextPointID();  

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