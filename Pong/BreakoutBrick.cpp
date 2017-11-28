#include "BreakoutBrick.h"

BreakoutBrick::BreakoutBrick()
{
}

BreakoutBrick::BreakoutBrick(sf::Vector2f startingPosition, sf::Vector2f rectangleSize)
{
	startingPositionVector2f = startingPosition;
	rectangleShape.setSize(rectangleSize);
	rectangleShape.setOrigin(rectangleSize / 2.0f);
}


BreakoutBrick::~BreakoutBrick()
{
}

void BreakoutBrick::update(float deltaTime)
{
}

void BreakoutBrick::start()
{
	rectangleShape.setPosition(startingPositionVector2f);
}

void BreakoutBrick::draw(sf::RenderWindow* window)
{
	window->draw(rectangleShape);
}
