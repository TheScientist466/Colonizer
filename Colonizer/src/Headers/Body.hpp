#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "Object.hpp"

class Body : public Object{

public:
	std::string name;
	ObjectTag tag = ObjectTag::Body;
	sf::Text powerText;
	int power;

private:
	float radius;
	float rotationSpeed;

	sf::CircleShape shape;
	sf::CircleShape miniShape;
	float powerIncreaseRate;
	

public:
	Body();
	Body(float radius, sf::Vector2f position, std::string name = "");

	sf::CircleShape* getShape();
	sf::CircleShape* getMiniShape();

	void setTexture(sf::Texture* t);
	void setTexture(sf::Texture* t, sf::Color averageColor);
	void setTextureRect(sf::Texture* t, sf::IntRect r);
	void setTextureRect(sf::Texture* t, sf::IntRect r, sf::Color averageColor);

	void rocketHit();
	void rocketLaunch();

	void update();
	void respondEvents(sf::Event e);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};