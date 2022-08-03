#pragma once

#include <SFML/Graphics.hpp>

#include "Object.hpp"

class Body : public Object{

private:
	float radius;
	sf::CircleShape shape;

public:
	Body();
	Body(float radius, sf::Vector2f position);

	sf::CircleShape* getShape();
	void update();
};