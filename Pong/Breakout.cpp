#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "Breakout.h"
#include "GameObject.h"
#include "BreakoutPaddle.h"
#include "BreakoutBall.h"
#include "BreakoutBrick.h"

using namespace std;
using namespace sf;

// Game Variables
bool gameIsDone;
int level;
int lives;
RenderWindow* window;
Vector2f windowSizeVectorf;
Vector2f windowCenterVectorf;
vector<GameObject*> gameObjects;
vector<BreakoutBrick*> bricks;
Clock gameClock;
BreakoutBall* ball;
BreakoutPaddle* paddle;

Breakout::Breakout() {} // Stub
Breakout::~Breakout() {} // Stub

void Breakout::play()
{
	init();
	generateBlocks();
	start();

	while (!gameIsDone && window->isOpen()) {
		poll(); // For Windows
		update();
		handleCollision();
		render();
	}
}

void Breakout::init() {
	// Get Path
	char path[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, path);
	MessageBoxA(NULL, path, "Current Directory", MB_OK);

	// Init Window
	windowSizeVectorf = Vector2f(600, 600);
	windowCenterVectorf = Vector2f(windowSizeVectorf.x / 2, windowSizeVectorf.y / 2);
	window = new RenderWindow(VideoMode(windowSizeVectorf.x, windowSizeVectorf.y), "Breakout");
	
	// Init Settings
	gameIsDone = false;
	level = 1;
	lives = 3;

	// Init static objects
	Vector2f paddleWidth(windowSizeVectorf.x/6, windowSizeVectorf.y/30);
	Vector2f paddlePosition(windowSizeVectorf.x/2, windowSizeVectorf.y*.9);
	ball = new BreakoutBall(windowCenterVectorf, windowSizeVectorf, 10, 100, 50);
	paddle = new BreakoutPaddle(paddlePosition, paddleWidth, windowSizeVectorf, 100);

	gameObjects.push_back(paddle);
	gameObjects.push_back(ball);
}

void Breakout::start() {
	for each(GameObject* gameObject in gameObjects) {
		gameObject->start();
	}
}

void Breakout::update() 
{
	float deltaTime = gameClock.restart().asSeconds();
	for each (GameObject* gameObject in gameObjects)
	{
		gameObject->update(deltaTime);
	}
}

void Breakout::handleCollision() {
	// Ball Hits Floor
	if (ball->circleShape.getPosition().y + ball->circleShape.getRadius() >= window->getSize().y) {
		die();
		window->setTitle(to_string(lives));
	}

	// Ball Hits Paddle
	if (rectCircleColliding(ball->circleShape, paddle->rectangleShape)) {
		float deltaX = ball->circleShape.getPosition().x - paddle->rectangleShape.getPosition().x;
		float rectHalfWidth = paddle->rectangleShape.getSize().x / 2;
		float diff = clampF(deltaX / rectHalfWidth, -1, 1);
		Vector2f newDirection = Vector2f(diff, -1);
		Vector2f newDirectionNormalized = newDirection / sqrt(newDirection.x * newDirection.x + newDirection.y * newDirection.y);
		ball->setDirection(newDirectionNormalized);
	}

	// Ball Hits Brick
	for (int x=0; x < bricks.size(); x++) {
		if (rectCircleColliding(ball->circleShape, bricks[x]->rectangleShape)) {
			Vector2f brickPosition = bricks[x]->rectangleShape.getPosition();
			Vector2f ballPosition = ball->circleShape.getPosition();
			Vector2f brickSize = bricks[x]->rectangleShape.getSize();
			float ballRadius = ball->circleShape.getRadius();
			float padding = 2;
			if (ballPosition.x - ballRadius + padding >= brickPosition.x + (brickSize.x/2) || ballPosition.x + ballRadius - padding <= brickPosition.x - (brickSize.x/2)) {
				ball->reverseX();
			} else {
				ball->reverseY();
			}
			gameObjects.erase(remove(gameObjects.begin(), gameObjects.end(), bricks[x]), gameObjects.end());
			bricks.erase(bricks.begin() + x);
		}
	}
}

void Breakout::render() 
{
	window->clear();
	for each (GameObject* gameObject in gameObjects)
	{
		gameObject->draw(window);
	}
	window->display();
}

void Breakout::poll() {
	Event event;
	while (window->pollEvent(event))
	{
		if (event.type == Event::Closed)
			window->close();
	}
}

void Breakout::generateBlocks() {
	float cellWidth = windowSizeVectorf.x / 6;
	float cellHeight = windowSizeVectorf.y / 10;
	float cellPositionX = windowSizeVectorf.x / 7;
	float cellPositionY = windowSizeVectorf.y / 11;
	float cellWidthOffset = (cellWidth - cellPositionX) + 7;
	float cellHeightOffset = (cellHeight - cellPositionY) + 7;
	for (int y = 1; y < 4; y++) {
		for (int x = 1; x < 5; x++) {
			BreakoutBrick* brickPtr = new BreakoutBrick(Vector2f(cellPositionX * (x + 1), cellPositionY * (y + 1)), Vector2f(cellWidth - cellWidthOffset, cellHeight - cellHeightOffset));
			gameObjects.push_back(brickPtr);
			bricks.push_back(brickPtr);
		}
	}
}

void Breakout::die() {
	lives--;
	ball->start();
}

bool Breakout::rectCircleColliding(CircleShape ball, RectangleShape paddle) {
	float ballRadius = ball.getRadius();
	Vector2f paddleSize = paddle.getSize();

	if (ball.getPosition().x - ballRadius <= paddle.getPosition().x + paddleSize.x / 2 &&
		ball.getPosition().x - ballRadius >= paddle.getPosition().x - paddleSize.x / 2 &&
		ball.getPosition().y + ballRadius >= paddle.getPosition().y - paddleSize.y / 2 &&
		ball.getPosition().y - ballRadius <= paddle.getPosition().y + paddleSize.y / 2)
		return true;
	if (ball.getPosition().x + ballRadius >= paddle.getPosition().x - paddleSize.x / 2 &&
		ball.getPosition().x + ballRadius <= paddle.getPosition().x + paddleSize.x / 2 &&
		ball.getPosition().y + ballRadius >= paddle.getPosition().y - paddleSize.y / 2 &&
		ball.getPosition().y - ballRadius <= paddle.getPosition().y + paddleSize.y / 2)
		return true;

	return false;
}

float Breakout::clampF(float value, float min, float max) {
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}