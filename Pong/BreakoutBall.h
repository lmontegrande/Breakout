#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "GameObject.h"

class BreakoutBall : public GameObject
{
private:
public:
	sf::CircleShape circleShape;
	sf::Vector2f directionVector2f;
	sf::Vector2f startingPositionVector2f;
	sf::Vector2f windowSizeVector2f;
	sf::Sound* hitWallSound;
	float speed;
	float speedModif;

	BreakoutBall();
	BreakoutBall(sf::Vector2f startPos, sf::Vector2f windowSize, float ballRadius, float s, float sm, sf::Sound* hitSound);
	~BreakoutBall();
	void update(float deltaTime);
	void setDirection(sf::Vector2f dir);
	void setDirection(float angle);
	void reverseY();
	void reverseX();
	void start();

	// Inherited via GameObject
	virtual void draw(sf::RenderWindow *) override;
};