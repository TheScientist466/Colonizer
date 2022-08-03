#include "Object.hpp"

sf::Time Object::deltaTime = sf::Time::Zero;

sf::Drawable* Object::getShape() {
	return shape;
}

void Object::update() { }

void Object::respondEvents(sf::Event e) { }