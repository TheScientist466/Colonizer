#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
//#include <array>

#include "Body.hpp"
#include "Rocket.hpp"

class ObjectManager {

private:
	const unsigned int numOfPlanets = 200;
	
	std::vector<Body> planets;
	std::vector<Rocket*> rockets;
	Body sun;

	std::vector<Object*>* objectsToDrawPtr;
	Body* lastSelected;

public:
	ObjectManager(std::vector<Object*>* objectsToDrawPtr);
	void update();
	void respondEvents(sf::Event e);

};