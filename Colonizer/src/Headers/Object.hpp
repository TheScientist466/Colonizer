#pragma once

#include <SFML/Graphics.hpp>

#include "Util.hpp"

struct Object {

public:
	static sf::Time deltaTime;
	static Input* inputSystem;
	sf::FloatRect hitbox;

protected:
	sf::Shape* shape;

public:
	virtual sf::Drawable* getShape();
	virtual void update();
	virtual void respondEvents(sf::Event e);
};