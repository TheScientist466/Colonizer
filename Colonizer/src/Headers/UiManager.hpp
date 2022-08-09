#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class UiManager {

public:
	UiManager(sf::RenderWindow* w, sf::View* camView);

private:
	sf::RenderWindow* gWindowPtr;
	sf::View* camView;
	std::vector<sf::Drawable*>* uiElementsPtr;
	std::vector<std::pair<sf::Text, std::string*>> dynamicTexts;
	std::vector<sf::Text> staticTexts;

	sf::Font uiFont;

	std::string framerate;
	std::string camPos[2];

public:
	static sf::Time deltaTime;

public:
	void draw();
	void addDynamicText(std::string* toUpdate, sf::Vector2f pos);
	//void addStaticText(std::string, sf::Vector2f pos);
	void update();


};