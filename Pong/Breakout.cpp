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
#include "UI.h"

using namespace std;
using namespace sf;

// Game Variables
bool gameIsDone;
bool roundIsDone;
int level;
int stage;
int lives;
int score;
RenderWindow* window;
Vector2f windowSizeVectorf;
Vector2f windowCenterVectorf;
vector<GameObject*> gameObjects;
vector<BreakoutBrick*> bricks;
UI* ui;
Clock gameClock;
BreakoutBall* ball;
BreakoutPaddle* paddle;

// Note to self, make an AudioManager class next time
Sound* paddleSound;
Sound* wallSound;
Sound* damageBrickSound;
Sound* destroyBrickSound;
Sound* loseLifeSound;
Sound* winLevelSound;
SoundBuffer sound1;
SoundBuffer sound2;
SoundBuffer sound3;
SoundBuffer sound4;
SoundBuffer sound5;
SoundBuffer sound6;

Breakout::Breakout() {} // Stub
Breakout::~Breakout() {} // Stub

void Breakout::play()
{
	init();
	updateUI();
	
	// Start State
	while (!gameIsDone && window->isOpen()) {
		generateBlocks();
		start();
		gameClock.restart();
		roundIsDone = false;
		// Round State
		while (!roundIsDone && window->isOpen()) {
			poll(); // For Windows
			update();
			handleCollision();
			render();
		}
	}

	// End State
	while (window->isOpen()) {
		poll();
		render();
	}

	cleanUp();
}

void Breakout::init() {
	// Get Path
	char path[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, path);
	//MessageBoxA(NULL, path, "Current Directory", MB_OK);

	// Init Window
	windowSizeVectorf = Vector2f(600, 600);
	windowCenterVectorf = Vector2f(windowSizeVectorf.x / 2, windowSizeVectorf.y / 2);
	window = new RenderWindow(VideoMode(windowSizeVectorf.x, windowSizeVectorf.y), "Breakout");
	
	// Init Settings
	gameIsDone = false;
	level = 1;
	stage = 1;
	lives = 3;

	// Init sounds
	sound1.loadFromFile("Resources/Blip_Select.wav");
	sound2.loadFromFile("Resources/Blip_Select2.wav");
	sound3.loadFromFile("Resources/Blip_Select3.wav");
	sound4.loadFromFile("Resources/Blip_Select4.wav");
	sound5.loadFromFile("Resources/Hit_Hurt.wav");
	sound6.loadFromFile("Resources/Pickup_Coin2.wav");
	paddleSound = new Sound(sound1);
	wallSound = new Sound(sound2);
	damageBrickSound = new Sound(sound3);
	destroyBrickSound = new Sound(sound4);
	loseLifeSound = new Sound(sound5);
	winLevelSound = new Sound(sound6);

	// Init persistent objects
	Vector2f paddleWidth(windowSizeVectorf.x/6, windowSizeVectorf.y/30);
	Vector2f paddlePosition(windowSizeVectorf.x/2, windowSizeVectorf.y*.9);
	ball = new BreakoutBall(windowCenterVectorf, windowSizeVectorf, 10, 300, 300, wallSound);
	paddle = new BreakoutPaddle(paddlePosition, paddleWidth, windowSizeVectorf, 200);
	ui = new UI(windowSizeVectorf, windowCenterVectorf);

	gameObjects.push_back(paddle);
	gameObjects.push_back(ball);
	gameObjects.push_back(ui);
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

void Breakout::cleanUp() {
	// Broken?
	/*for each (GameObject* gameObject in gameObjects) {
		delete gameObject;
	}
	for each (BreakoutBrick* brick in bricks) {
		delete brick;
	}*/
	delete window;
	delete ui;
	delete ball;
	delete paddle;
	delete paddleSound;
	delete wallSound;
	delete damageBrickSound;
	delete destroyBrickSound;
	delete loseLifeSound;
	delete winLevelSound;
}

void Breakout::handleCollision() {
	// Ball Hits Floor
	if (ball->circleShape.getPosition().y + ball->circleShape.getRadius() >= window->getSize().y) {
		die();
		window->setTitle(to_string(lives));
	}

	// Ball Hits Paddle
	if (rectCircleColliding(ball->circleShape, paddle->rectangleShape)) {
		paddleSound->play();
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
			if (bricks[x]->wasHitLastFrame) {
				break;
			}
			bricks[x]->wasHitLastFrame = true;
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

			if (bricks[x]->getHit()) {
				destroyBrickSound->play();
				gameObjects.erase(remove(gameObjects.begin(), gameObjects.end(), bricks[x]), gameObjects.end());
				bricks.erase(bricks.begin() + x);
				score += 1 * level;
				updateUI();
				if (bricks.size() == 0) {
					winRound();
				}
			} else {
				damageBrickSound->play();
			}
			break;
		} else {
			bricks[x]->wasHitLastFrame = false;
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
			int hp = level;
			bool isMoving = false;
			bool isStealth = false;
			if (stage % 2 == 0) {
				isMoving = true;
			}
			if (stage % 3 == 0) {
				isStealth = true;
			}
			Vector2f startingPosition = Vector2f(cellPositionX * (x + 1), cellPositionY * (y + 1));
			Vector2f size = Vector2f(cellWidth - cellWidthOffset, cellHeight - cellHeightOffset);
			BreakoutBrick* brickPtr = new BreakoutBrick(startingPosition, size, hp, isMoving, isStealth);
			gameObjects.push_back(brickPtr);
			bricks.push_back(brickPtr);
		}
	}
}

void Breakout::winRound() {
	winLevelSound->play();
	roundIsDone = true;
	stage++;
	if (stage == 4) {
		ball->speed += ball->speedModif;
		paddle->speed += ball->speedModif;
		stage = 1;
		level++;
	}
}

void Breakout::die() {
	loseLifeSound->play();
	if (lives <= 0) {
		gameIsDone = true;
		roundIsDone = true;
		ui->showEndText = true;
	} else {
		lives--;
		updateUI();
		ball->start();
		paddle->start();
	}
}

void Breakout::updateUI() {
	ui->setLives(lives);
	ui->setScore(score);
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