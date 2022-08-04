#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Util.hpp"
#include "Body.hpp"
#include "ObjectManager.hpp"

class Game {

public:
	Game();

public:
	std::vector<Object*> objectsToDraw;
	std::vector<sf::Drawable*> uiElements;

private:
	sf::RenderWindow gWindow;
	sf::View gCamera;
	sf::Vector2i gCameraDir;
	sf::Clock gClock;

	Input inputSystem;
	ObjectManager objMgr;

public:
	void mainLoop();

private:
	void respondEvents();
	void update();
	void cameraMovement(sf::Keyboard::Key k, bool isReleased);

};
