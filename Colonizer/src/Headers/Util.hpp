#pragma once

#include <SFML/Graphics.hpp> 

enum class Space {
	ScreenSpace,
	WindowSpace,
	WorldSpace
};

class Input {
	
public:
	Input(sf::RenderWindow* window, sf::View* worldView);

private:
	sf::View* worldViewPtr;
	sf::RenderWindow* windowPtr;
	sf::Event windowEvents;

public:
	sf::Vector2i getMousePos(Space s);
	bool pollEvent();
	sf::Event getEvent();
};