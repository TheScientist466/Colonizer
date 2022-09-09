#include "Object.hpp"

sf::Time Object::deltaTime = sf::Time::Zero;
Input* Object::inputSystem = nullptr;
TextureManager* Object::textureManager = nullptr;
sf::Font* Object::defaultFont = nullptr;

sf::Drawable* Object::getShape() {
	return shape;
}

sf::Drawable* Object::getMiniShape() {
	return shape;
}

void Object::update() { }

void Object::respondEvents(sf::Event e) { }

void Object::draw(sf::RenderTarget&, sf::RenderStates) const { }

TextObject::TextObject(sf::Font& _f) : text(sf::Text("", _f)), miniDraw(false) { }

void TextObject::draw(sf::RenderTarget& _t, sf::RenderStates _s) const {
	if(toDraw)
		_t.draw(text, _s);
}

sf::Drawable* TextObject::getMiniShape() {
	return &text;
}

sf::Drawable* TextObject::getShape() {
	return &text;
}