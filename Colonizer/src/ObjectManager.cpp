#include "ObjectManager.hpp"
#include "constants.hpp"

ObjectManager::ObjectManager(std::vector<Object*>* _objToDrawPtr) :
	objectsToDrawPtr(_objToDrawPtr)
{
	srand(time(0));

	for(unsigned int i = 0; i < numOfPlanets; i++) {
		int randVal1 = rand() % 10 + 10, randVal2 = rand() % WINDOW_WIDTH + 1, randVal3 = rand() % WINDOW_HEIGHT + 1;
		planets.push_back(Body(randVal1, sf::Vector2f(randVal2, randVal3)));
	}
	sun = Body(50, sf::Vector2f(WINDOW_WIDTH >> 1, WINDOW_HEIGHT >> 1));
	objectsToDrawPtr->push_back(&sun);

	for(auto& a : planets)
		objectsToDrawPtr->push_back(&a);
}

void ObjectManager::update() {

}