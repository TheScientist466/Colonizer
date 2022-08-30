#include "Object.hpp"

sf::Time Object::deltaTime = sf::Time::Zero;
Input* Object::inputSystem = nullptr;
TextureManager* Object::textureManager = nullptr;

sf::Drawable* Object::getShape() {
	return shape;
}

sf::Drawable* Object::getMiniShape() {
	return shape;
}

void Object::update() { }

void Object::respondEvents(sf::Event e) { }