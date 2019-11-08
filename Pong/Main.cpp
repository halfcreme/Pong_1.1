// TODO: add high score for all time
// TODO: add death screen
// TODO: add start screen
// TODO: add sound
// TODO: add random powerups/powerdowns

#include "ball.h"
#include "paddle.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
	int windowWidth = 1024, windowHeight = 768;
	RenderWindow window(VideoMode(windowWidth, windowHeight), "Pong");
	window.setVerticalSyncEnabled(true);

	int score = 0;
	int highScore = 0;
	int lives = 3;

	Paddle paddle(windowWidth / 2.0, windowHeight - 20.0);
	Ball ball(windowWidth / 2.0, 1.0);

	Text hud;
	Font font;
	font.loadFromFile("DS-DIGIT.TTF");
	hud.setFont(font);
	hud.setCharacterSize(75);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		// Left key to move left
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			if (paddle.getPosition().left > 0)
				paddle.moveLeft();
		}

		// Right key to move right
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			if (paddle.getPosition().left + 65 < windowWidth)
				paddle.moveRight();
		}

		// Escape key to close window
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Ball out of bounds at bottom
		if (ball.getPosition().top > windowHeight)
		{
			ball.hitBottom();
			lives--; // decrease lives by -1

			// If no lives left, reset game
			if (lives < 1)
			{
				if (score > highScore)
					highScore = score;
				score = 0;
				lives = 3;
			}
		}

		// Ball rebounding off sides
		if (ball.getPosition().left < 0 || ball.getPosition().left + 10 > windowWidth)
		{
			ball.reboundSides();
		}

		// Ball hitting top
		if (ball.getPosition().top < 0)
		{
			ball.reboundPadOrTop();
			score++;
		}
		
		// Ball hitting paddle
		if (ball.getPosition().intersects(paddle.getPosition()))
		{
			ball.reboundPadOrTop();
		}

		ball.update();
		paddle.update();

		// Update HUD text
		std::stringstream ss;
		ss << "High score: " << highScore << endl
			<< "Score: " << score << "     Lives: " << lives;
		hud.setString(ss.str());
		
		window.clear(Color(26, 128, 182, 255)); // light blue screen
		window.draw(paddle.getShape());
		window.draw(ball.getShape());
		window.draw(hud);
		window.display();
	}
	
	return 0;
}