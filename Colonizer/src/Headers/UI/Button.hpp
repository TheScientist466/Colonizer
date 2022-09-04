#pragma once

#include <SFML/Graphics.hpp>

template <class T>
class Button {

public:
	Button(sf::FloatRect _r, T* _obj, void (*_a)(Button&, T&)) {
		obj = _obj;
		hitbox = _r;
		onClick = _a;

		shape = sf::RectangleShape(sf::Vector2f(hitbox.width, hitbox.height));
		shape.setPosition(sf::Vector2f(hitbox.left, hitbox.top));
	}

public:
	bool isClicked = false;

private:
	T* obj;
	sf::FloatRect hitbox;
	sf::RectangleShape shape;
	sf::Text text;
	void (*onClick)(Button&, T&);

public:
	void Click() {
		isClicked = true;
		shape.setFillColor(sf::Color(0xaaaaaaff));
		onClick(*this, *obj);
	}

	sf::FloatRect getHitbox() {
		return hitbox;
	}
	sf::RectangleShape* getShape() {
		return &shape;
	}
};