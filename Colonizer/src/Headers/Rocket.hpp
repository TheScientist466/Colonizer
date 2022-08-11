#pragma once

#include "Object.hpp"

#include <SFML/Graphics.hpp>

class Rocket : public Object {
public:
	Rocket();
	Rocket(sf::Vector2f pos);
	Rocket(sf::Vector2f pos, sf::Vector2f velocity);
	Rocket(sf::Vector2f pos, sf::Vector2f dir, float speed);

private:
	sf::Sprite shape;
	sf::Vector2f velocity;

public:
	static sf::Texture* tex;
	bool miniDraw = false;

public:
	sf::Sprite* getShape();
	void update();
};