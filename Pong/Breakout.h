#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "GameObject.h"

class Breakout
{
public:
	Breakout();
	~Breakout();

	void play();
	void init();
	void start();
	void update();
	void handleCollision();
	void render();
	void poll();
	void generateBlocks();
	void die();
	bool rectCircleColliding(sf::CircleShape ball, sf::RectangleShape paddle);
	float clampF(float value, float min, float max);
};

