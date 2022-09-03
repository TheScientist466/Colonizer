#pragma once

#include <SFML/Graphics.hpp>

class Button {

public:
	Button();
	Button(sf::FloatRect rect, void (*onClick)(Button&));

public:
	bool isClicked = false;

private:
	sf::FloatRect hitbox;
	sf::RectangleShape shape;
	sf::Text text;
	void (*onClick)(Button&);

public:
	void Click();
	sf::FloatRect getHitbox();
	sf::RectangleShape* getShape();
};