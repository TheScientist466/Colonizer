#include "Body.hpp"

Body::Body() : radius(0), shape(0)
{}

Body::Body(float _rad, sf::Vector2f _pos) :
	radius(_rad)
{
	shape = sf::CircleShape(radius, 8U);
	shape.setOrigin(radius, radius);
	shape.setPosition(_pos);
}

sf::CircleShape* Body::getShape() {
	return &shape;
}

void Body::update() {
	shape.rotate(60.f * deltaTime.asSeconds());
}