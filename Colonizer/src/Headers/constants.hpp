#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#define WINDOW_HEIGHT config::window::WINDOW_DIMENTIONS.y
#define WINDOW_WIDTH config::window::WINDOW_DIMENTIONS.x

const sf::Vector2i UP_VECTOR2		= sf::Vector2i( 0,  1);
const sf::Vector2i DOWN_VECTOR2		= sf::Vector2i( 0, -1);
const sf::Vector2i LEFT_VECTOR2		= sf::Vector2i(-1,  0);
const sf::Vector2i RIGHT_VECTOR2	= sf::Vector2i( 1,  0);
const sf::Vector2i ZERO_VECTOR2		= sf::Vector2i( 0,  0);

namespace config {
	namespace window {
		const sf::Vector2i WINDOW_DIMENTIONS = sf::Vector2i(500, 500);
		const std::string WINDOW_TITLE = "Title";
	}
}