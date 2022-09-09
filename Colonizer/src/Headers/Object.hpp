#pragma once

#include <SFML/Graphics.hpp>

#include "Util.hpp"

struct Object : public sf::Drawable {

public:
	ObjectTag tag = ObjectTag::PureObject;

	static sf::Time deltaTime;
	static Input* inputSystem;
	static TextureManager* textureManager;
	static sf::Font* defaultFont;
	sf::FloatRect hitbox;

	bool miniDraw;

protected:
	sf::Shape* shape;

public:
	virtual sf::Drawable* getShape();
	virtual sf::Drawable* getMiniShape();
	virtual void update();
	virtual void respondEvents(sf::Event e);

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};