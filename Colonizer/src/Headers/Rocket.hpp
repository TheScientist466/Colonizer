#pragma once

#include "Object.hpp"
#include "Body.hpp"
#include "constants.hpp"

#include <SFML/Graphics.hpp>

class Rocket : public Object {
public:
	Rocket(Body* parent);
	Rocket(Body* parent, sf::Vector2f pos);
	Rocket(Body* parent, sf::Vector2f pos, sf::Vector2f velocity);
	Rocket(Body* parent, sf::Vector2f pos, sf::Vector2f dir, float speed);

private:
	sf::Sprite shape;
	sf::Vector2f velocity;

	int dieCtr = 3 * config::window::framerate;

public:
	ObjectTag tag = ObjectTag::Rocket;
	const Body* parent;

	static sf::Texture* tex;
	bool miniDraw = false;
	bool isHit = false;
	bool toDestroy = false;

public:
	sf::Sprite* getShape();
	void update();
};