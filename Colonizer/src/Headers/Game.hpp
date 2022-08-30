#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <array>

#include "Util.hpp"
#include "Body.hpp"
#include "ObjectManager.hpp"
#include "UiManager.hpp"
#include "Minimap.hpp"

class Game {

public:
	Game();
	~Game();

public:
	std::vector<Object*> objectsToDraw;

private:
	sf::RenderWindow gWindow;
	sf::View gCamera;
	sf::Vector2i gCameraDir;
	float gCameraSpeed = 400.f;
	sf::Clock gClock;

	Minimap minimap;

	UiManager uiMgr;
	Input inputSystem;
	ObjectManager objMgr;
	TextureManager* texMgr;

public:
	void mainLoop();

private:
	void respondEvents();
	void update();
	void cameraMovement(sf::Keyboard::Key k, bool isReleased);

};
