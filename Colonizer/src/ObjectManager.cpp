#include "ObjectManager.hpp"
#include "constants.hpp"

#include <string>

ObjectManager::ObjectManager(std::vector<Object*>* _objToDrawPtr) :
	objectsToDrawPtr(_objToDrawPtr)
{
	sun = Body(50, sf::Vector2f(WINDOW_WIDTH >> 1, WINDOW_HEIGHT >> 1), "SUN");

	srand(time(0));
	for(unsigned int i = 0; i < numOfPlanets; i++) {

		int randVal1 = rand() % 10 + 10, randVal2 = rand() % (WINDOW_WIDTH - randVal1) + 1, randVal3 = rand() % (WINDOW_HEIGHT - randVal1) + 1;
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

		if(isSpawnablePos)
			planets.push_back(Body(randVal1, pos, std::to_string(i)));
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