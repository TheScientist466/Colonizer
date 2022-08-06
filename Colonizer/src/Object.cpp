#include "Object.hpp"

sf::Time Object::deltaTime = sf::Time::Zero;
Input* Object::inputSystem = nullptr;

sf::Drawable* Object::getShape() {
	return shape;
}

void Object::update() { }

void Object::respondEvents(sf::Event e) { }