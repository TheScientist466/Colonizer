#include "Minimap.hpp"

const float MAP_DIV = 3;

Minimap::Minimap(std::vector<Object*>* _objs, sf::View* _camView) :
	objsToDraw(_objs),
	camView(_camView),
	shape(sf::Vector2f(WINDOW_WIDTH / MAP_DIV, WINDOW_HEIGHT / MAP_DIV))
{
	mapTexture.create(MAP_WIDTH, MAP_HEIGHT);
	mapTexture.setView(sf::View(sf::Vector2f(0, 0), sf::Vector2f(MAP_WIDTH, -MAP_HEIGHT)));
	mapTexture.clear(sf::Color::White);

	shape.setTexture(&mapTexture.getTexture());
	shape.setPosition(WINDOW_WIDTH - (WINDOW_WIDTH / MAP_DIV), 0);
	shape.setOutlineThickness(5.f);
	shape.setOutlineColor(sf::Color::White);

	cameraPos = sf::CircleShape(50);
	cameraPos.setFillColor(sf::Color::Red);

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
}