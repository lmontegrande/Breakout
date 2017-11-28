#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

class BreakoutPaddle : public GameObject
{
public:
	BreakoutPaddle();
	BreakoutPaddle(sf::Vector2f startingPos, sf::Vector2f size, sf::Vector2f windowDim,float speed);
	~BreakoutPaddle();

	sf::RectangleShape rectangleShape;
	sf::Vector2f directionVector2f;
	sf::Vector2f positionVector2f;
	sf::Vector2f startingPositionVector2f;
	sf::Vector2f windowDimensionsVector2f;
	float speed;

	// Inherited via GameObject
	virtual void update(float deltaTime) override;
	virtual void start() override;
	virtual void draw(sf::RenderWindow *) override;
	float clampF(float value, float min, float max);
};

