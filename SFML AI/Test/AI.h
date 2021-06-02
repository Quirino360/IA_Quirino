#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Player.h"

namespace gl {

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
		~AI() = default;

		void Init();
		void Update();
		void Render(sf::RenderWindow* window);
		void Destroy();

		sf::CircleShape playerCircleShape;


	private:
		unsigned int ID = 0;
		sf::Shape* playerShape = nullptr;
		sf::Texture player_Texture;

		sf::Vector2f playerPosition;

		//steering beahviors
		sf::Vector2f target;
		float maxVelocity = 4;  //before 2
		float maxSpeed = 10;		//before 2
		float maxForce = 2;
		float mass = 1;

	public:


		/*
		Seek ---------- YA
		Flee ---------- YA
		Arrive ---------- YA
		Pursuit ---------- YA
		Evade ---------- YA
		Wander ---------- TO_UPGRADE
		Path Following ---------- TO_DO
		Collition Avoidance ---------- TO_DO
		Flocking ---------- TO_DO


		Examen ---------- TO_DO
		/**/
		void SteeringBehaiviorSeek(sf::Vector2f _target);
		void SteeringBehaiviorFlee(sf::Vector2f _target);
		void SteeringBehaiviorArrival(sf::Vector2f _target);

		void SteeringBehaiviorWander(); //Mejorar collition y la manera de hacerlo
		void SteeringBehaiviorPersuit(gl::Player _target);
		void SteeringBehaiviorSeekEvade(gl::Player _target);

		void SteeringBehaviorPathFollowing();
		void SteeringBehaviorCollisionAvoidance();
		void SteeringBehaviorFlocking();

		sf::Vector2f GetPlayerPosition() { return playerPosition; };

		void SetPlayerPosition(sf::Vector2f pos) { playerPosition = pos; };

	private:
		sf::Vector2f NormalizeVector(sf::Vector2f A);
		sf::Vector2f TruncateVector(sf::Vector2f A, float x);
		float DistanceBetweenVectors(sf::Vector2f A, sf::Vector2f B);
		sf::Vector2f Wander();

		//path folowing
		std::vector<PathPoint> nodes;
		int nodeID = 0;
		PathPoint pathPointTarget;

		void CreateDefaultPath();
		void AddPathPoint(PathPoint _point) { nodes.push_back(_point); };
		int GetNextPointID();  

	};
}


