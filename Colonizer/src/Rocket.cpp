#include "Rocket.hpp"

#include "Util.hpp"
#include "constants.hpp"

#include <cmath>

sf::Texture* Rocket::tex;

Rocket::Rocket(Body* _p) :
	parent(_p)
{
	shape.setTexture(*tex);
	shape.setScale(.08, .08);
}

Rocket::Rocket(Body* _p, sf::Vector2f pos) :
	parent(_p)
{
	shape.setPosition(pos);
}

Rocket::Rocket(Body* _p, sf::Vector2f pos, sf::Vector2f _vel) :
	parent(_p)
{
	shape.setTexture(*tex);
	shape.setScale(.08, .08);
	shape.setPosition(pos);
	sf::Vector2f direction = normalizeVector(velocity);
	shape.setRotation((atan2f(direction.y, direction.x) * 180.f / PI) + 90);

	velocity = _vel;
}

Rocket::Rocket(Body* _p, sf::Vector2f pos, sf::Vector2f direction, float speed) :
	parent(_p)
{
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

	if(isHit) {
		dieCtr--;
		velocity /= 1.01f;
		shape.scale(sf::Vector2f(0.9f, 0.9f));
		if(dieCtr < 0)
			toDestroy = true;
	}
}