#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "Object.hpp"

class Body : public Object{

public:
	std::string name;

private:
	float radius;
	sf::CircleShape shape;

public:
	Body();
	Body(float radius, sf::Vector2f position, std::string name = "");

	sf::CircleShape* getShape();
	void update();
	void respondEvents(sf::Event e);
};