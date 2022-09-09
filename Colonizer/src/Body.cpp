#include "Body.hpp"

#include "Util.hpp"

#include <iostream>
#include <string>

Body::Body() : radius(0), shape(0)
{}

Body::Body(float _rad, sf::Vector2f _pos, std::string _name) :
	radius(_rad)
{
	name = _name;
	miniDraw = true;

	shape = sf::CircleShape(radius, 32U);
	shape.setOrigin(radius, radius);
	shape.setPosition(_pos);
	miniShape = shape;
	miniShape.setPosition(_pos);

	hitbox.top = _pos.y - _rad;
	hitbox.left = _pos.x - _rad;
	hitbox.height = _rad * 2;
	hitbox.width = _rad * 2;

	rotationSpeed = getRandBetween(30, 180);
	rotationSpeed *= getRandBetween(-100, 100) < 0 ? -1 : 1;

	power = getRandBetween(1, 20);
	if(Object::defaultFont != nullptr) {
		powerText = sf::Text(std::to_string(power), *Object::defaultFont, _rad);
		powerText.setFillColor(sf::Color::White);
		powerText.setPosition(_pos - sf::Vector2f(_rad / 2, _rad / 2));
		powerText.setStyle(sf::Text::Bold);
	}
}

sf::CircleShape* Body::getShape() {
	return &shape;
}

void Body::update() {
	shape.rotate(rotationSpeed * deltaTime.asSeconds());

	hitbox.top = shape.getPosition().y - shape.getRadius();
	hitbox.left = shape.getPosition().x - shape.getRadius();
}

void Body::respondEvents(sf::Event e) {	}

sf::CircleShape* Body::getMiniShape()
{
	return &miniShape;
}

void Body::setTexture(sf::Texture* t) {
	shape.setTexture(t);

	miniShape.setFillColor(getAverageColor(t));
}

void Body::setTexture(sf::Texture* t, sf::Color c) {
	shape.setTexture(t);

	miniShape.setFillColor(c);
}

void Body::setTextureRect(sf::Texture* t, sf::IntRect r) {
	shape.setTexture(t);
	shape.setTextureRect(r);

	miniShape.setFillColor(getAverageColor(t));
}

void Body::setTextureRect(sf::Texture* t, sf::IntRect r, sf::Color c) {
	shape.setTexture(t);
	shape.setTextureRect(r);

	miniShape.setFillColor(c);
}

void Body::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(shape, states);
	target.draw(powerText, states);
}

void Body::rocketHit() {
	power++;
	powerText.setString(std::to_string(power));
}

void Body::rocketLaunch() {
	power--;
	powerText.setString(std::to_string(power));
}