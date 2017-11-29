#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "GameObject.h"

class UI : public GameObject
{
public:
	sf::Font font;
	sf::Text scoreText;
	sf::Text livesText;
	sf::Text endText;
	sf::Vector2f windowSizeVectorf;
	bool showEndText;

	UI();
	UI(sf::Vector2f, sf::Vector2f);
	~UI();

	// Inherited via GameObject
	virtual void update(float deltaTime) override;
	virtual void start() override;
	virtual void draw(sf::RenderWindow *) override;
	void setLives(int lives);
	void setScore(int score);
};

