#include "UiManager.hpp"

sf::Time UiManager::deltaTime = sf::Time::Zero;

const unsigned int FRAMERATE_CHECK_DELAY = 20;
unsigned int updateCtr = 0;

UiManager::UiManager(sf::RenderWindow* w, sf::View* _camView) :
	gWindowPtr(w),
	camView(_camView)
{
	uiFont.loadFromFile("./Assets/Alice-Regular.ttf");
	this->addDynamicText(&framerate, sf::Vector2f(20, 70));
	this->addDynamicText(&camPos[0], sf::Vector2f(20, 20));
	this->addDynamicText(&camPos[1], sf::Vector2f(120, 20));
}

void UiManager::draw() {
	for(auto& a: dynamicTexts)
		gWindowPtr->draw(a.first);

	for(sf::Text& a : staticTexts)
		gWindowPtr->draw(a);
}

void UiManager::update() {

	if(updateCtr % FRAMERATE_CHECK_DELAY == 0)
		framerate = std::to_string((int)(1 / deltaTime.asSeconds()));
	camPos[0] = std::to_string((int)camView->getCenter().x);
	camPos[1] = std::to_string((int)camView->getCenter().y);


	for(std::pair<sf::Text, std::string*>& a : dynamicTexts)
		a.first.setString(*a.second);

	updateCtr++;
}

void UiManager::addDynamicText(std::string* s, sf::Vector2f pos)
{
	sf::Text t;
	t.setFont(uiFont);
	t.setFillColor(sf::Color::White);
	t.setPosition(pos);
	t.setCharacterSize(32);
	t.setString(*s);
	std::pair<sf::Text, std::string*> p;
	p.first = t;
	p.second = s;

	dynamicTexts.push_back(p);
}