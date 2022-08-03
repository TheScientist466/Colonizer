#pragma once

#include <SFML/Graphics.hpp>

struct Object {

public:
	static sf::Time deltaTime;

protected:
	sf::Shape* shape;

public:
	virtual sf::Drawable* getShape();
	virtual void update();
	virtual void respondEvents(sf::Event e);
};