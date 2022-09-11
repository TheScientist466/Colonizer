#include "ObjectManager.hpp"
#include "constants.hpp"
#include "Util.hpp"
#include "Rocket.hpp"

#include <string>
#include <iostream>
#include <cmath>
#include <array>

bool clickedPlanet = false;

ObjectManager::ObjectManager(std::vector<Object*>* _objToDrawPtr, TextureManager* _texMgrPtr) :
	objectsToDrawPtr(_objToDrawPtr)
{
	_texMgrPtr = new TextureManager("./Assets/mainTexture.png");
	Object::textureManager = _texMgrPtr;

	Object::defaultFont = new sf::Font();
	Object::defaultFont->loadFromFile("./Assets/Comfortaa-VariableFont_wght.ttf");

	sun = Body(100, sf::Vector2f(0, 0), "SUN");
	sun.setTextureRect(Object::textureManager->getTexture(), Object::textureManager->getRect(ObjectTag::Sun, 0), Object::textureManager->getMinimapColor(ObjectTag::Sun, 0));

	planets.push_back(sun);

	srand((unsigned int)time(0));
	for(unsigned int i = 0; i < numOfPlanets; i++) {

		int radius = getRandBetween(10, 30), posX = getRandBetween(-1 * (MAP_WIDTH >> 1), MAP_WIDTH >> 1), posY = getRandBetween(-1 * (MAP_HEIGHT >> 1), MAP_HEIGHT >> 1);
		sf::Vector2f pos(posX, posY);
		bool isSpawnablePos = true;
		
		if(getDistSq(sun.getShape()->getPosition(), pos) <= powf(sun.getShape()->getRadius() + radius + 10.f, 2))
			isSpawnablePos = false;
		else {
			for(auto& a : planets) {
				if(getDistSq(a.getShape()->getPosition(), pos) <= powf(a.getShape()->getRadius() + radius + 10.f, 2)) {
					isSpawnablePos = false;
					break;
				}
			}
		}

		if(isSpawnablePos) {
			float distFormSun = getDist(pos, sun.getShape()->getPosition());
			Body b(radius, pos, std::to_string(i));

			int randVal = getRandBetween(1, 100);
			int planetType = 0;

			if(distFormSun <= 1000) {
				if(randVal <= 60)
					planetType = 3;
				else if(randVal <= 80)
					planetType = 2;
				else
					planetType = 1;
			}
			else if(distFormSun <= 2000){
				if(randVal <= 80)
					planetType = 6;
				else if(randVal <= 90)
					planetType = 0;
				else
					planetType = 4;
			}
			else {
				if(randVal <= 80)
					planetType = 5;
				else
					planetType = 6;
			}

			b.setTextureRect(Object::textureManager->getTexture(), Object::textureManager->getRect(ObjectTag::Body, planetType), Object::textureManager->getMinimapColor(ObjectTag::Body, planetType));
			planets.push_back(b);
		}
		else {
			i--;
			continue;
		}
	}

	for(auto& a : planets)
		objectsToDrawPtr->push_back(&a);

	lastSelected = nullptr;

	mouseText = TextObject(*Object::defaultFont);
	objectsToDrawPtr->push_back(&mouseText);
	mouseText.toDraw = false;
	mouseLine.toDraw = false;
	objectsToDrawPtr->push_back(&mouseLine);
}

ObjectManager::~ObjectManager() {
	for(auto a : rockets)
		delete a;
	delete Object::defaultFont;
}

void ObjectManager::update() {
	sun.update();
	for(auto& a : planets)
		a.update();

	for(unsigned int i = 0; i < rockets.size(); i++) {
		sf::Vector2f rocketPos = rockets[i]->getShape()->getPosition();
		if(!config::world::MAP.contains(static_cast<sf::Vector2i>(rocketPos))) {
			rockets[i]->toDestroy = true;
		}

		if(!(rockets[i]->isHit || rockets[i]->toDestroy)) {
			for(auto& a : planets) {
				if(&a != rockets[i]->parent) {
					if(a.hitbox.contains(rockets[i]->getShape()->getPosition())) {
						a.rocketHit();
						rockets[i]->isHit = true;
						break;
					}
				}
			}
		}

		if(rockets[i]->toDestroy) {
			delete rockets[i];
			for(unsigned int k = 0; k < objectsToDrawPtr->size(); k++) {
				if(rockets[i] == (*objectsToDrawPtr)[k])
					objectsToDrawPtr->erase(objectsToDrawPtr->begin() + k);
			}
			rockets.erase(rockets.begin() + i);
		}
		else
			rockets[i]->update();
	}

	if(mouseText.toDraw) {
		if(lastSelected != nullptr && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2f mousePos = static_cast<sf::Vector2f>(Object::inputSystem->getMousePos(Space::WorldSpace));
			unsigned int dist = getDistSq(lastSelected->getShape()->getPosition(), mousePos);
			unsigned int maxRocketsToShoot = std::clamp((dist / 4000), 0U, (unsigned int)lastSelected->power);
			sf::Vector2f offset = sf::Vector2f(10, 10);
			mouseText.text.setPosition(static_cast<sf::Vector2f>(mousePos) + offset);
			mouseText.text.setCharacterSize(20 * log(maxRocketsToShoot) + 14);
			mouseText.text.setString(std::to_string(maxRocketsToShoot));

			mouseLine.line[0] = mousePos;
			mouseLine.line[1] = lastSelected->getShape()->getPosition();
		}
	}
}

void ObjectManager::respondEvents(sf::Event e) {
	if(e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Button::Left) {
		clickedPlanet = false;
		for(auto& p : planets) {
			if(p.hitbox.contains(static_cast<sf::Vector2f>(Object::inputSystem->getMousePos(Space::WorldSpace)))) {
				if(lastSelected != nullptr)
					lastSelected->getShape()->setFillColor(sf::Color::White);
				lastSelected = &p;
				lastSelected->getShape()->setFillColor(sf::Color::Green);
				clickedPlanet = true;
				break;
			}
		}
		if(!clickedPlanet && lastSelected != nullptr) {
			mouseText.toDraw = true;
			mouseLine.toDraw = true;
		}
	}
	else if(e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left) {
		if(!clickedPlanet && lastSelected != nullptr) {
			float lastRad = lastSelected->getShape()->getRadius() - 5.f;
			float dist = getDistSq(lastSelected->getShape()->getPosition(), static_cast<sf::Vector2f>(Object::inputSystem->getMousePos(Space::WorldSpace)));
			unsigned int maxToShoot = std::clamp((unsigned int)(dist / 4000), 0U, (unsigned int)lastSelected->power);
			for(int i = 0; i < maxToShoot; i++) {
				sf::Vector2f offset = sf::Vector2f(getRandBetween(-lastRad, lastRad), getRandBetween(-lastRad, lastRad));
				Rocket* r = new Rocket(lastSelected,
									   lastSelected->getShape()->getPosition() + offset,
									   static_cast<sf::Vector2f>(Object::inputSystem->getMousePos(Space::WorldSpace)) - lastSelected->getShape()->getPosition(),
									   100.f);
				r->setTextureRect(Object::textureManager->getTexture(), Object::textureManager->getRect(ObjectTag::Rocket, getRandBetween(0, 5)));
				rockets.push_back(r);
				objectsToDrawPtr->push_back(r);
				lastSelected->rocketLaunch();
			}
			mouseText.toDraw = false;
			mouseLine.toDraw = false;
			lastSelected->getShape()->setFillColor(sf::Color::White);
			lastSelected = nullptr;
		}
	}
}