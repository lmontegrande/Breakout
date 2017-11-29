#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "GameObject.h"

class BreakoutBrick : public GameObject
{
public:
	int health;
	bool isMovingBrick;
	bool isStealthBrick;
	bool wasHitLastFrame;
	float speed;
	sf::Vector2f direction;
	sf::RectangleShape rectangleShape;
	sf::Vector2f startingPositionVector2f;

	BreakoutBrick();
	BreakoutBrick(sf::Vector2f startingPosition, sf::Vector2f rectangleSize, int hp, bool isMoving, bool isStealth);
	~BreakoutBrick();

	// Inherited via GameObject
	virtual void update(float deltaTime) override;
	virtual void start() override;
	virtual void draw(sf::RenderWindow *) override;
	void updateColor();
	bool getHit();
};