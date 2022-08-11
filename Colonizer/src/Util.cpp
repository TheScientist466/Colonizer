#include "Util.hpp"

#include <constants.hpp>

#include <cmath>
#include <random>

std::mt19937 rng(time(0));

Input::Input(sf::RenderWindow* _w, sf::View* _v) :
	windowPtr(_w),
	worldViewPtr(_v)
{ }

sf::Vector2i Input::getMousePos(Space s) {
	if(s == Space::ScreenSpace)
		return sf::Mouse::getPosition();
	else if(s == Space::WindowSpace)
		return sf::Mouse::getPosition(*windowPtr);
	else if(s == Space::WorldSpace)
		return sf::Vector2i(sf::Mouse::getPosition(*windowPtr).x + worldViewPtr->getCenter().x - (windowPtr->getSize().x >> 1),
							sf::Mouse::getPosition(*windowPtr).y + worldViewPtr->getCenter().y - (windowPtr->getSize().y >> 1));
}

bool Input::pollEvent() {
	return windowPtr->pollEvent(windowEvents);
}

sf::Event Input::getEvent() {
	return windowEvents;
}

float getDistSq(sf::Vector2f a, sf::Vector2f b) {
	return powf(a.x - b.x, 2) + powf(a.y - b.y, 2);
}

float getDist(sf::Vector2f a, sf::Vector2f b) {
	return sqrtf(getDistSq(a, b));
}

int getRandBetween(int min, int max) {
	//int randNum = rand() % (max - min + 1) + min;
	//return randNum;

	
	std::uniform_int_distribution<int> gen(min, max); // uniform, unbiased
	int r = gen(rng);
	return r;
}

sf::Vector2f normalizeVector(sf::Vector2f a) {
	return a / getDist(a, static_cast<sf::Vector2f>(ZERO_VECTOR2));
}

void initUtil() {
	//rng(time(0));
}