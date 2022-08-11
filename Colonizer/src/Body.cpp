#include "Body.hpp"

#include "Util.hpp"

#include <iostream>

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
