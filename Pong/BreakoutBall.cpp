#include "BreakoutBall.h"   

BreakoutBall::BreakoutBall() {}

BreakoutBall::BreakoutBall(sf::Vector2f staringPosition, sf::Vector2f windowSize, float ballRadius, float s, float sm) {
	startingPositionVector2f = staringPosition;
	windowSizeVector2f = windowSize;
	directionVector2f = sf::Vector2f(0, 1);
	circleShape.setRadius(ballRadius);
	speed = s;
	speedModif = sm;
	circleShape.setOrigin(ballRadius / 2, ballRadius / 2);
}

BreakoutBall::~BreakoutBall()
{
}

void BreakoutBall::start()
{
	circleShape.setPosition(startingPositionVector2f);
	directionVector2f = sf::Vector2f(0, 1);
}

void BreakoutBall::draw(sf::RenderWindow* window)
{
	window->draw(circleShape);
}

void BreakoutBall::update(float deltaTime)
{
	circleShape.move(directionVector2f * speed * deltaTime);
	circleShape.setOrigin(circleShape.getRadius(), circleShape.getRadius());
	circleShape.rotate(speed * deltaTime);

	sf::Vector2f currentPosition = circleShape.getPosition();
	float radius = circleShape.getRadius();

	// Hit left
	if (currentPosition.x <= radius) {
		directionVector2f.x = abs(directionVector2f.x);
	}
	// Hit right
	if (currentPosition.x >= windowSizeVector2f.x - radius) {
		directionVector2f.x = -abs(directionVector2f.x);
	}
	// Hit top
	if(currentPosition.y <= radius) {
		directionVector2f.y = abs(directionVector2f.y);
	}
	// Hit bottom
	if (currentPosition.y >= windowSizeVector2f.y - radius) {
		directionVector2f.y = -abs(directionVector2f.y);
	}
}

void BreakoutBall::setDirection(sf::Vector2f direction) {
	directionVector2f = direction/(direction.x*direction.x + direction.y*direction.y);
}

void BreakoutBall::setDirection(float angle) {
	directionVector2f = sf::Vector2f(cos(angle), sin(angle));
}

void BreakoutBall::reverseY() {
	directionVector2f.y = -directionVector2f.y;
}

void BreakoutBall::reverseX() {
	directionVector2f.x = -directionVector2f.x;
}