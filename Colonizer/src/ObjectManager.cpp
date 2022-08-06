#include "ObjectManager.hpp"
#include "constants.hpp"
#include "Util.hpp"

#include <string>
#include <iostream>

ObjectManager::ObjectManager(std::vector<Object*>* _objToDrawPtr) :
	objectsToDrawPtr(_objToDrawPtr)
{
	sf::Texture* sunTexture = new sf::Texture();
	sunTexture->loadFromFile("./Assets/Sun.png");

	sun = Body(100, sf::Vector2f(0, 0), "SUN");
	sun.getShape()->setTexture(sunTexture);

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
			b.getShape()->setTexture(bodyTexture);
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