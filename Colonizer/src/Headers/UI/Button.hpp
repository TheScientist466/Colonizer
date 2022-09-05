#pragma once

#include <SFML/Graphics.hpp>

template <class T>
class Button : public sf::Drawable {

public:
	Button(sf::FloatRect _r, T* _obj, void (*_onClick)(Button&, T&), void (*_onRelease)(Button&, T&)) {
		obj = _obj;
		hitbox = _r;
		onClick = _onClick;
		onRelease = _onRelease;

		shape = sf::RectangleShape(sf::Vector2f(hitbox.width, hitbox.height));
		shape.setPosition(sf::Vector2f(hitbox.left, hitbox.top));

		sf::Font* f = new sf::Font();
		if(f->loadFromFile("./Assets/Comfortaa-VariableFont_wght.ttf")) {
			text = sf::Text("Button", *f, 32);
			text.setStyle(1);
			text.setFillColor(sf::Color::Black);
			text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
			text.setPosition(hitbox.left + (hitbox.width / 4), hitbox.top + (hitbox.height / 4));
		}
	}

	~Button() {
		delete text.getFont();
	}

public:
	bool isClicked = false;
	sf::Color clickedColor = sf::Color(0xaaaaaaff);
	sf::Color releasedColor = sf::Color(0xffffffff);
	sf::Text text;
	int id = 0;

private:
	T* obj;
	sf::FloatRect hitbox;
	sf::RectangleShape shape;
	void (*onClick)(Button&, T&);
	void (*onRelease)(Button&, T&);

public:
	void Click() {
		isClicked = true;
		shape.setFillColor(clickedColor);
		if(onClick != nullptr)
			onClick(*this, *obj);
	}

	void Release() {
		isClicked = false;
		shape.setFillColor(releasedColor);
		if(onRelease != nullptr)
			onRelease(*this, *obj);
	}

	sf::FloatRect getHitbox() {
		return hitbox;
	}
	sf::RectangleShape* getShape() {
		return &shape;
	}
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(shape, states);
		target.draw(text);
	}
};