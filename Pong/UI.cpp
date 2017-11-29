#include "UI.h"

UI::UI()
{
}

UI::UI(sf::Vector2f windowSize, sf::Vector2f windowCenterVectorf)
{
	windowSizeVectorf = windowSize;
	font.loadFromFile("Resources/sansation.ttf");
	scoreText.setFont(font);
	livesText.setFont(font);

	scoreText.setCharacterSize(40);
	livesText.setCharacterSize(40);
	scoreText.setPosition(windowCenterVectorf.x - 250, 30);
	livesText.setPosition(windowCenterVectorf.x + 90, 30);
	scoreText.setFillColor(sf::Color::Blue);
	livesText.setFillColor(sf::Color::Cyan);

	endText.setFont(font);
	endText.setCharacterSize(50);
	endText.setPosition(windowCenterVectorf);
	endText.setFillColor(sf::Color::Red);
	endText.setOrigin(windowCenterVectorf.x / 2, 0);
	endText.setString("Game Over");

	showEndText = false;
}

UI::~UI()
{
}

void UI::update(float deltaTime)
{
}

void UI::start()
{
}

void UI::draw(sf::RenderWindow* window)
{
	window->draw(scoreText);
	window->draw(livesText);
	if (showEndText)
		window->draw(endText);
}

void UI::setLives(int lives) {
	livesText.setString("Lives: " + std::to_string(lives));
}

void UI::setScore(int score) {
	scoreText.setString("Score: " + std::to_string(score));
}
