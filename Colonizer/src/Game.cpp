#include "constants.hpp"
#include "Game.hpp"
#include "Body.hpp"
#include "Util.hpp"

#include <iostream>
#include <SFML/Graphics/Text.hpp>

Game::Game() :
	gWindow(sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Title", sf::Style::Close, sf::ContextSettings(0, 0, 2))),
	gCamera(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT)),
	inputSystem(&gWindow, &gCamera),
	objMgr(&objectsToDraw)
{
	gWindow.setFramerateLimit(60);
}

void Game::mainLoop() {
	gClock.restart();

	while(gWindow.isOpen()) {
		while(inputSystem.pollEvent()) {
			respondEvents();
		}
		gWindow.clear();
		update();
		gWindow.setView(gCamera);

		for(auto& i : objectsToDraw)
			gWindow.draw(*(i->getShape()));

		gWindow.setView(gWindow.getDefaultView());

		for(auto& i : uiElements)
			gWindow.draw(*i);

		gWindow.display();
		Object::deltaTime = gClock.restart();
	}
}

void Game::respondEvents() {
	sf::Event buffer = inputSystem.getEvent();
	switch(buffer.type) {
		case sf::Event::Closed:
			gWindow.close();
			break;
		case sf::Event::KeyPressed:
			cameraMovement(buffer.key.code, false);
			break;
		case sf::Event::KeyReleased:
			cameraMovement(buffer.key.code, true);
			break;
	}
}

void Game::cameraMovement(sf::Keyboard::Key _k, bool _isReleased) {
	int inv = _isReleased ? 1 : -1;

	if(_k == sf::Keyboard::W)
		gCameraDir += UP_VECTOR2 * inv;
	else if(_k == sf::Keyboard::S)
		gCameraDir += DOWN_VECTOR2 * inv;

	if(_k == sf::Keyboard::A)
		gCameraDir += RIGHT_VECTOR2 * inv;
	else if(_k == sf::Keyboard::D)
		gCameraDir += LEFT_VECTOR2 * inv;

	gCameraDir = sf::Vector2i(std::clamp(gCameraDir.x, -1, 1), std::clamp(gCameraDir.y, -1, 1));
}

void Game::update() {
	gCamera.move(static_cast<sf::Vector2f>(gCameraDir));

	for(auto& i : objectsToDraw)
		i->update();
}