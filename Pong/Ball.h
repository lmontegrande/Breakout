#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "GameObject.h"

class Ball : public GameObject
{ 
private:
public: 
	sf::CircleShape circleShape; 
	sf::Vector2f directionVector2f;
	sf::Vector2f startingPositionVector2f;
	sf::Vector2f windowSizeVector2f;
	float speed; 
	float speedModif;

	Ball();
	Ball(sf::Vector2f startPos, sf::Vector2f windowSize, float ballRadius, float s, float sm);
	~Ball();
	void update(float deltaTime);
	void changeDirection(float angle);
	void changeDirection(sf::Vector2f direction);
	void reverseY();
	void reverseX();
	void start();

	// Inherited via GameObject
	virtual void draw(sf::RenderWindow *) override;
};