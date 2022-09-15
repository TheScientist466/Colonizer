#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "constants.hpp"
#include "Object.hpp"

class Minimap : Object {

public:
	Minimap(std::vector<Object*>* objsToDraw, sf::View* camView, bool isLive);

private:
	sf::RenderTexture mapTexture;
	sf::RectangleShape shape;
	sf::CircleShape cameraPos;

	std::vector<Object*>* objsToDraw;
	sf::View* camView;
	bool isLive;

public:
	sf::Drawable* getShape();
	void update(bool toForceUpdate = false);

};