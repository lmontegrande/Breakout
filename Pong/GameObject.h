#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

class GameObject
{
public:
	virtual void update(float deltaTime) = 0;
	virtual void start() = 0;
	virtual void draw(sf::RenderWindow*) = 0;
};

