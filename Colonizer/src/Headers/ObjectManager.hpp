#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
//#include <array>

#include "Body.hpp"

class ObjectManager {

private:
	const unsigned int numOfPlanets = 200;
	
	std::vector<Body> planets;
	Body sun;

	std::vector<Object*>* objectsToDrawPtr;
	Body* lastSelected;

public:
	ObjectManager(std::vector<Object*>* objectsToDrawPtr);
	void update();
	void respondEvents(sf::Event e);

};