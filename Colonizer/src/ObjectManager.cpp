#include "ObjectManager.hpp"
#include "constants.hpp"
#include "Util.hpp"
#include "Rocket.hpp"

#include <string>
#include <iostream>

ObjectManager::ObjectManager(std::vector<Object*>* _objToDrawPtr) :
	objectsToDrawPtr(_objToDrawPtr)
{
	sf::Texture* sunTexture = new sf::Texture();
	sunTexture->loadFromFile("./Assets/Sun.png");

	sf::Texture* RocketTexture = new sf::Texture();
	Rocket::tex = RocketTexture;
	RocketTexture->loadFromFile("./Assets/Rocket1.png");
	RocketTexture->generateMipmap();
	RocketTexture->setSmooth(true);

	sun = Body(100, sf::Vector2f(0, 0), "SUN");
	sun.setTexture(sunTexture, getAverageColor(sunTexture));

	sf::Texture* bodyTexture = new sf::Texture();
	if(!bodyTexture->loadFromFile("./Assets/Planet1.png")) {
		sf::Image* k = new sf::Image();
		k->create(500, 500);

		for(unsigned int i = 0; i < k->getSize().y; i++) {
			for(unsigned int j = 0; j < k->getSize().x; j++) {
				k->setPixel(j, i, sf::Color(0, j, i));
			}
		}

		bodyTexture->loadFromImage(*k);
	}
	sf::Color averageBodyColor = getAverageColor(bodyTexture);

	srand(time(0));
	for(unsigned int i = 0; i < numOfPlanets; i++) {

		int randVal1 = getRandBetween(10, 30), randVal2 = getRandBetween(-1 * (MAP_WIDTH >> 1), MAP_WIDTH >> 1), randVal3 = getRandBetween(-1 * (MAP_HEIGHT >> 1), MAP_HEIGHT >> 1);
		sf::Vector2f pos(randVal2, randVal3);
		bool isSpawnablePos = true;
		
		if(getDistSq(sun.getShape()->getPosition(), pos) <= powf(sun.getShape()->getRadius() + randVal1 + 10.f, 2))
			isSpawnablePos = false;
		else {
			for(auto& a : planets) {
				if(getDistSq(a.getShape()->getPosition(), pos) <= powf(a.getShape()->getRadius() + randVal1 + 10.f, 2)) {
					isSpawnablePos = false;
					break;
				}
			}
		}

		if(isSpawnablePos) {
			Body b = Body(randVal1, pos, std::to_string(i));
			b.setTexture(bodyTexture, averageBodyColor);
			planets.push_back(b);
		}
		else {
			i--;
			continue;
		}
	}
	objectsToDrawPtr->push_back(&sun);

	for(auto& a : planets)
		objectsToDrawPtr->push_back(&a);
}

void ObjectManager::update() {

}

void ObjectManager::respondEvents(sf::Event e) {

	if(e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Button::Left) {
		bool clickedPlanet = false;
		for(auto& p : planets) {

			if(p.hitbox.contains(static_cast<sf::Vector2f>(Object::inputSystem->getMousePos(Space::WorldSpace)))) {
				if(lastSelected != nullptr)
					lastSelected->getShape()->setFillColor(sf::Color::White);
				lastSelected = &p;
				lastSelected->getShape()->setFillColor(sf::Color::Green);
				clickedPlanet = true;
			}
		}

		if(!clickedPlanet && lastSelected != nullptr) {
			objectsToDrawPtr->push_back(new Rocket(lastSelected->getShape()->getPosition(),
												   static_cast<sf::Vector2f>(Object::inputSystem->getMousePos(Space::WorldSpace)) - lastSelected->getShape()->getPosition(),
												   100.f));
			lastSelected->getShape()->setFillColor(sf::Color::White);
			lastSelected = nullptr;
		}
	}
}