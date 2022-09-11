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

Line::Line(sf::Vector2f _a, sf::Vector2f _b) :
	line(sf::LinesStrip, 2),
	toDraw(true),
	miniDraw(false)
{
	line[0].position = _a;
	line[1].position = _b;
}

sf::Drawable* Line::getShape() {
	return &line;
}

sf::Drawable* Line::getMiniShape() {
	return &line;
}

void Line::draw(sf::RenderTarget& _t, sf::RenderStates _s) const {
	if(toDraw)
		_t.draw(line, _s);
}

