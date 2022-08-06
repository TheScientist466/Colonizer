#include "Body.hpp"

#include "Util.hpp"

#include <iostream>

Body::Body() : radius(0), shape(0)
{}

Body::Body(float _rad, sf::Vector2f _pos, std::string _name) :
	radius(_rad)
{
	name = _name;

	shape = sf::CircleShape(radius, 32U);
	shape.setOrigin(radius, radius);
	shape.setPosition(_pos);

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

void Body::respondEvents(sf::Event e) {
	if(e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Button::Left) {

		if(hitbox.contains(static_cast<sf::Vector2f>(inputSystem->getMousePos(Space::WorldSpace)))) {
			std::cout << name << " is clicked" << std::endl;
		}
	}
}