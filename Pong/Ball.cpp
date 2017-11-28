#include "Ball.h"   

Ball::Ball() {}

Ball::Ball(sf::Vector2f staringPosition, sf::Vector2f windowSize, float ballRadius, float s, float sm) {
	startingPositionVector2f = staringPosition;
	windowSizeVector2f = windowSize;
	directionVector2f = sf::Vector2f(0, 1);
	circleShape.setRadius(ballRadius);
	speed = s;
	speedModif = sm;
	circleShape.setOrigin(ballRadius / 2, ballRadius / 2);
}
 
Ball::~Ball()
{
}

void Ball::start()
{
	circleShape.setPosition(startingPositionVector2f);
}

void Ball::draw(sf::RenderWindow* window)
{
	window->draw(circleShape);
}

void Ball::update(float deltaTime)
{
	circleShape.move(directionVector2f * speed * deltaTime);
	circleShape.setOrigin(circleShape.getRadius(), circleShape.getRadius());
	circleShape.rotate(speed * deltaTime);
}

void Ball::changeDirection(float angle) {
	directionVector2f = sf::Vector2f(cos(angle), sin(angle));
}

void Ball::changeDirection(sf::Vector2f dir) {
	directionVector2f = sf::Vector2f(dir); // Assumes dir has been normalized
}

void Ball::reverseY() {
	directionVector2f.y = -directionVector2f.y;
}

void Ball::reverseX() {
	directionVector2f.x = -directionVector2f.x;
}