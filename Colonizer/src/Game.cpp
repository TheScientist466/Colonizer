#include "constants.hpp"
#include "Game.hpp"
#include "Object.hpp"
#include "Body.hpp"
#include "Util.hpp"

#include <iostream>
#include <string>
#include <SFML/Graphics/Text.hpp>

Game::Game() :
	gWindow(sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Title", sf::Style::Close, sf::ContextSettings(0, 0, 2))),
	gCamera(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT)),
	inputSystem(&gWindow, &gCamera),
	objMgr(&objectsToDraw)
{
	gWindow.setFramerateLimit(60);
	Object::inputSystem = &inputSystem;
	
	gCamera.setCenter(sf::Vector2f(0, 0));

	uiFont.loadFromFile("./Assets/Alice-Regular.ttf");

	gCameraPosUI[0].setFont(uiFont);
	gCameraPosUI[1].setFont(uiFont);
	gCameraPosUI[0].setCharacterSize(32);
	gCameraPosUI[1].setCharacterSize(32);
	gCameraPosUI[0].setPosition(20, 20);
	gCameraPosUI[1].setPosition(120, 20);
	gCameraPosUI[0].setFillColor(sf::Color::White);
	gCameraPosUI[1].setFillColor(sf::Color::White);

	uiElements.push_back(&gCameraPosUI[0]);
	uiElements.push_back(&gCameraPosUI[1]);

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

	for(auto& a : objectsToDraw) {
		a->respondEvents(buffer);
	}

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

	gCameraPosUI[0].setString(std::to_string((int)gCamera.getCenter().x));
	gCameraPosUI[1].setString(std::to_string((int)gCamera.getCenter().y));

	for(auto& i : objectsToDraw)
		i->update();
}