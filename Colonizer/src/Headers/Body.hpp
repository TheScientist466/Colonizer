#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "Object.hpp"

class Body : public Object{

public:
	std::string name;

private:
	float radius;
	float rotationSpeed;

	sf::CircleShape shape;
	sf::CircleShape miniShape;

public:
	Body();
	Body(float radius, sf::Vector2f position, std::string name = "");

	sf::CircleShape* getShape();
	sf::CircleShape* getMiniShape();

	void setTexture(sf::Texture* t);
	void setTexture(sf::Texture* t, sf::Color averageColor);

	void update();
	void respondEvents(sf::Event e);
};