#include "UI/Button.hpp"

Button::Button() { }

Button::Button(sf::FloatRect _r, void (*a)(Button&)) {
	hitbox = _r;
	onClick = a;

	shape = sf::RectangleShape(sf::Vector2f(hitbox.width, hitbox.height));
	shape.setPosition(sf::Vector2f(hitbox.left, hitbox.top));
}

void Button::Click() {
	isClicked = true;
	shape.setFillColor(sf::Color(0xaaaaaaff));
	onClick(*this);
}

sf::FloatRect Button::getHitbox() {
	return hitbox;
}

sf::RectangleShape* Button::getShape() {
	return &shape;
}