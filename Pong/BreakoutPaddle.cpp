#include "BreakoutPaddle.h"


BreakoutPaddle::BreakoutPaddle()
{
}

BreakoutPaddle::BreakoutPaddle(sf::Vector2f startingPosition, sf::Vector2f rectSize, sf::Vector2f windowDimensions, float s) 
{
	startingPositionVector2f = startingPosition;
	windowDimensionsVector2f = windowDimensions;
	rectangleShape.setSize(rectSize);
	rectangleShape.setOrigin(rectSize / 2.0f);
	speed = s;
}

BreakoutPaddle::~BreakoutPaddle()
{
}

void BreakoutPaddle::update(float deltaTime)
{
	sf::Keyboard::Key leftKey = sf::Keyboard::A;
	sf::Keyboard::Key rightKey = sf::Keyboard::D;

	int xAxisDir = 0;
	if (sf::Keyboard::isKeyPressed(leftKey)) xAxisDir -= 1;
	if (sf::Keyboard::isKeyPressed(rightKey)) xAxisDir += 1;

	rectangleShape.move(sf::Vector2f(xAxisDir * speed * deltaTime, 0));

	float currentX = rectangleShape.getPosition().x;
	float currentY = rectangleShape.getPosition().y;
	float halfWidth = rectangleShape.getSize().x / 2;
	rectangleShape.setPosition(clampF(currentX, halfWidth, windowDimensionsVector2f.x - halfWidth), currentY);
}

void BreakoutPaddle::start()
{
	rectangleShape.setPosition(startingPositionVector2f);
}

void BreakoutPaddle::draw(sf::RenderWindow* window)
{
	window->draw(rectangleShape);
}

float BreakoutPaddle::clampF(float value, float min, float max) {
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}