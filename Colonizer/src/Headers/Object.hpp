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
	bool toDraw = true;

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

/*Some Useful Objects*/
class TextObject : public Object {
public:
	ObjectTag tag = ObjectTag::Text;
	sf::Text text;
	TextObject(sf::Font& f = *Object::defaultFont);
	virtual sf::Drawable* getShape();
	virtual sf::Drawable* getMiniShape();
	bool toDraw;
	bool miniDraw;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};