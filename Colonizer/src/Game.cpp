#include "constants.hpp"
#include "Game.hpp"
#include "Object.hpp"
#include "Body.hpp"
#include "Util.hpp"
#include "UiManager.hpp"

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

Game::Game() :
	gWindow(sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Title", config::window::TO_FULLSCREEN ? sf::Style::Fullscreen : sf::Style::Close, sf::ContextSettings(0, 0, 2))),
	gCamera(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT)),
	inputSystem(&gWindow, &gCamera),
	objMgr(&objectsToDraw),
	uiMgr(&gWindow, &gCamera),
	minimap(&objectsToDraw, &gCamera, false)
{
	gWindow.setFramerateLimit(config::window::framerate);
	Object::inputSystem = &inputSystem;
	
	gCamera.setCenter(sf::Vector2f(0, 0));
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

		uiMgr.draw();
		gWindow.draw(*minimap.getShape());

		gWindow.display();
		Object::deltaTime = gClock.restart();
		UiManager::deltaTime = Object::deltaTime;
	}
}

void Game::respondEvents() {
	sf::Event buffer = inputSystem.getEvent();

	objMgr.respondEvents(buffer);

	for(auto& a : objectsToDraw) {
		a->respondEvents(buffer);
	}

	switch(buffer.type) {
		case sf::Event::Closed:
			gWindow.close();
			break;
		case sf::Event::KeyPressed:
			cameraMovement(buffer.key.code, false);
			if(buffer.key.code == sf::Keyboard::Q)
				gWindow.close();
			break;
		case sf::Event::KeyReleased:
			cameraMovement(buffer.key.code, true);
			break;
	}
}

void Game::cameraMovement(sf::Keyboard::Key _k, bool _isReleased) {
	int inv = _isReleased ? 1 : -1;

	if(_k == sf::Keyboard::W || _k == sf::Keyboard::Up)
		gCameraDir += UP_VECTOR2 * inv;
	else if(_k == sf::Keyboard::S || _k == sf::Keyboard::Down)
		gCameraDir += DOWN_VECTOR2 * inv;

	if(_k == sf::Keyboard::A || _k == sf::Keyboard::Left)
		gCameraDir += RIGHT_VECTOR2 * inv;
	else if(_k == sf::Keyboard::D || _k == sf::Keyboard::Right)
		gCameraDir += LEFT_VECTOR2 * inv;

	gCameraDir = sf::Vector2i(std::clamp(gCameraDir.x, -1, 1), std::clamp(gCameraDir.y, -1, 1));
}

void Game::update() {
	gCamera.move(static_cast<sf::Vector2f>(gCameraDir) * gCameraSpeed * Object::deltaTime.asSeconds());
	objMgr.update();
	minimap.update();
	uiMgr.update();
}