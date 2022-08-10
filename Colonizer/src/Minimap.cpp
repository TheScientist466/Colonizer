#include "Minimap.hpp"

const float MAP_DIV = 4;

Minimap::Minimap(std::vector<Object*>* _objs, sf::View* _camView) :
	objsToDraw(_objs),
	camView(_camView),
	shape(sf::Vector2f(WINDOW_HEIGHT / MAP_DIV, WINDOW_HEIGHT / MAP_DIV))
{
	mapTexture.create(MAP_WIDTH, MAP_HEIGHT);
	mapTexture.setView(sf::View(sf::Vector2f(0, 0), sf::Vector2f(MAP_WIDTH, -MAP_HEIGHT)));
	mapTexture.clear(sf::Color::White);

	shape.setTexture(&mapTexture.getTexture());
	shape.setOrigin(shape.getSize().x, 0);
	shape.setPosition(WINDOW_WIDTH, 0);
	shape.setOutlineThickness(5.f);
	shape.setOutlineColor(sf::Color::White);

	cameraPos = sf::CircleShape(20);
	cameraPos.setOrigin(20, 20);
	cameraPos.setFillColor(sf::Color::Red);

	hitbox = sf::FloatRect(WINDOW_WIDTH - shape.getSize().x, 0, shape.getSize().x, shape.getSize().y);
}

sf::Drawable* Minimap::getShape() {
	return &shape;
}

void Minimap::update() {
	cameraPos.setPosition(camView->getCenter());
	mapTexture.clear(sf::Color::Black);

	for(auto& a : *objsToDraw)
		mapTexture.draw(*a->getShape());
	mapTexture.draw(cameraPos);
	mapTexture.generateMipmap();
	mapTexture.setSmooth(true);

	if(hitbox.contains(static_cast<sf::Vector2f>(inputSystem->getMousePos(Space::WindowSpace))))
		shape.setScale(3, 3);
	else
		shape.setScale(1, 1);
}