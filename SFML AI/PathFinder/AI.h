#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "SteeringBehavior.h"

enum class AI_STATE_TYPE;
enum class ANIMATION_AI_STATE_TYPE;

namespace gl 
{
	/*
		los estados tienen que estar en el amespce compiladores.
		Semantico, leer que estado es, y guardarlo en analizador lexico
		si es un error, se le manda al error manager al lexico
	*/

	/**
	* @brief   manages the Artificial Intelegence behaviors
	* @bug     NA	*/
	class AI
	{
	public:

		AI() = default;
		~AI() = default;

		/**
		* @brief   Initializes the AI variables
		* @param   NA
		* @bug     NA
		* @return  #void		*/
		void Init(sf::Vector2f _position = {0, 0});

		/**
		* @brief   updates the AI position
		* @param   NA
		* @bug     NA
		* @return  #void		*/
		void Update();
		
		/**
		* @brief   renders the AI shape
		* @param   sf::RenderWindow* to render the AI shapes
		* @bug     NA
		* @return  #void		*/
		void Render(sf::RenderWindow* window);

		/**
		* @brief   releses memory
		* @param   NA
		* @bug     NA
		* @return  #void		*/
		void Destroy();

		//Captre the flag
		AI_STATE_TYPE* AI_State;
		ANIMATION_AI_STATE_TYPE* AI_AnimState;

		bool restart = false;
		unsigned int gameResult = 0; // NA = 0, Win = 1, Loose = 2;

		//animation
		float fps = 0.0f;
		unsigned int currentFrame = 0;
		std::vector<sf::IntRect> animation;

	private:
		bool hasTargetAI = false;
		/*sf::CircleShape* threadObstacle;/**/

		//AI	
		sf::CircleShape AI_CircleShape;
		unsigned int ID = 0;
		sf::Shape* playerShape = nullptr;
		sf::Texture texture;
		sf::Vector2f position;
		sf::Vector2f direction;

		// Steering Behavior
		SteeringBehavior sBehavior;
		sf::Vector2f velocity;
		float maxVelocity = 2;  //before 2
		float maxSpeed = 2;	//before 2
		float maxForce = 2;
		float mass = 1;

	public:

		void Animate();


		// Getters ------------------------- //
		/**
		* @brief   get the shape position
		* @param   NA
		* @bug     NA
		* @return  sf::Vector2f		*/
		sf::Vector2f GetPosition() { return position; };

		/**
		* @brief   get the AI velocity
		* @param   NA
		* @bug     NA
		* @return  sf::Vector2f		*/
		sf::Vector2f GetVelocity() { return velocity; };

		sf::Vector2f GetDirection() { return direction; };

		/**
		* @brief   get the current steering behavior
		* @param   NA
		* @bug     NA
		* @return  SteeringBehavior		*/
		SteeringBehavior& GetSteeringBehavior() { return sBehavior; };


		// Setters ------------------------- //
		/**
		* @brief   set the player position
		* @param   sf::Vector2f the new AI position
		* @bug     NA
		* @return  #void		*/
		void SetPosition(sf::Vector2f _pos) { position = _pos; AI_CircleShape.setPosition(position); };

		void SetAnimation(std::vector<sf::IntRect> _newAnim) { animation = _newAnim; };


		//void SetVelocity(sf::Vector2f _vel) { velocity = _vel; };

		/**
		* @brief   Sets new max velocity
		* @param   #float new max velocity
		* @bug     NA
		* @return  #void		*/
		void SetMaxVelocity(float _maxVelocity) { maxVelocity = _maxVelocity; };

		/**
		* @brief   set new steering behavior to the AI
		* @param   BEHAVIOR the new behavior
		* @bug     NA
		* @return  #void		*/

		void SetSteeringBehavior(BEHAVIOR _newBehavior) { sBehavior.SetBehavior(_newBehavior); };

		void SetCircleColor(sf::Color _newColor) { AI_CircleShape.setFillColor(_newColor); };


	private:


		bool TouchedGoal();


		bool lineIntersectsAI(sf::Vector2f _ahead, sf::Vector2f _ahead2, AI obstacle); // Capture the flag


		AI findMostThreateningAI(sf::Vector2f _ahead, sf::Vector2f _ahead2); // Capture the flag


		// Utilities
		/**
		* @brief   Normalizes a vector
		* @param   #sf::Vector2f vector to normalize
		* @bug     NA
		* @return  sf::Vector2f normalized vector		*/
		sf::Vector2f NormalizeVector(sf::Vector2f A);

		/**
		* @brief   Gets the Distance Between Vectors
		* @param   sf::Vector2f A
		* @param   sf::Vector2f B
		* @bug     NA
		* @return  #float Distance Between Vectors*/
		float DistanceBetweenVectors(sf::Vector2f A, sf::Vector2f B);

	};
}