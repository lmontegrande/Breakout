#include "BreakoutBrick.h"

BreakoutBrick::BreakoutBrick()
{
}

BreakoutBrick::BreakoutBrick(sf::Vector2f startingPosition, sf::Vector2f rectangleSize, int hp, bool isMoving, bool isStealth)
{
	health = hp;
	isMovingBrick = isMoving;
	isStealthBrick = isStealth;
	startingPositionVector2f = startingPosition;
	rectangleShape.setSize(rectangleSize);
	rectangleShape.setOrigin(rectangleSize / 2.0f);
	updateColor();
	wasHitLastFrame = false;
	speed = 100;
	direction = sf::Vector2f(1, 0);
}


BreakoutBrick::~BreakoutBrick()
{

}

void BreakoutBrick::update(float deltaTime)
{
	// Stealth
	static float stealthTimer = 0;
	static float stealthTime = 1;
	if (isStealthBrick) {
		stealthTimer += deltaTime;
		if (stealthTimer >= stealthTime) {
			stealthTimer = 0;
			if (rectangleShape.getFillColor() == sf::Color::Transparent) {
				updateColor();
			} else {
				rectangleShape.setFillColor(sf::Color::Transparent);
			}
		}
	}

	// Moving
	float moveMaxDistance = rectangleShape.getSize().x;
	if (isMovingBrick) {
		if (rectangleShape.getPosition().x - startingPositionVector2f.x >= moveMaxDistance) {
			direction = sf::Vector2f(-1,0);
		}
		if (rectangleShape.getPosition().x - startingPositionVector2f.x <= -moveMaxDistance) {
			direction = sf::Vector2f(1,0);
		}
		rectangleShape.move(direction * speed * deltaTime);
	}
}

void BreakoutBrick::start()
{
	rectangleShape.setPosition(startingPositionVector2f);
}

void BreakoutBrick::draw(sf::RenderWindow* window)
{
	window->draw(rectangleShape);
}

void BreakoutBrick::updateColor() {
	switch (health) {
	case 1:
		rectangleShape.setFillColor(sf::Color::White);
		break;
	case 2:
		rectangleShape.setFillColor(sf::Color::Magenta);
		break;
	default:
		rectangleShape.setFillColor(sf::Color::Yellow);
	}
}

bool BreakoutBrick::getHit() {
	bool isDead = false;
	health--;
	updateColor();
	if (health <= 0) {
		isDead = true;
	}

	return isDead;
}
