#include "Rocket.hpp"

#include "Util.hpp"
#include "constants.hpp"

#include <cmath>

sf::Texture* Rocket::tex;

Rocket::Rocket() {
	shape.setTexture(*tex);
	shape.setScale(.08, .08);
}

Rocket::Rocket(sf::Vector2f pos) {
	shape.setPosition(pos);
}

Rocket::Rocket(sf::Vector2f pos, sf::Vector2f _vel) {
	shape.setTexture(*tex);
	shape.setScale(.08, .08);
	shape.setPosition(pos);

	velocity = _vel;
}

Rocket::Rocket(sf::Vector2f pos, sf::Vector2f direction, float speed) {
	shape.setTexture(*tex);
	shape.setScale(.08, .08);
	shape.setPosition(pos);
	shape.setRotation((atan2f(direction.y, direction.x) * 180.f / PI) + 90);

	velocity = normalizeVector(direction) * speed;
}

sf::Sprite* Rocket::getShape() {
	return &shape;
}

void Rocket::update() {
	shape.move(velocity * deltaTime.asSeconds());
}