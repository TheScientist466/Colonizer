#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#define WINDOW_HEIGHT config::window::WINDOW_DIMENTIONS.y
#define WINDOW_WIDTH config::window::WINDOW_DIMENTIONS.x

#define MAP_HEIGHT config::world::MAP_SIZE.y
#define MAP_WIDTH config::world::MAP_SIZE.x

const sf::Vector2i UP_VECTOR2		= sf::Vector2i( 0,  1);
const sf::Vector2i DOWN_VECTOR2		= sf::Vector2i( 0, -1);
const sf::Vector2i LEFT_VECTOR2		= sf::Vector2i(-1,  0);
const sf::Vector2i RIGHT_VECTOR2	= sf::Vector2i( 1,  0);
const sf::Vector2i ZERO_VECTOR2		= sf::Vector2i( 0,  0);

const float PI = 3.141592653589793238f;

namespace config {
	struct window {
		static sf::Vector2i WINDOW_DIMENTIONS;
		static bool TO_FULLSCREEN;

		static std::string WINDOW_TITLE;
		static const unsigned int framerate = 60;
	};
	namespace world {
		const sf::Vector2i MAP_SIZE = sf::Vector2i(5000, 5000);
		const sf::IntRect MAP = sf::IntRect(-(MAP_SIZE.x >> 1), -(MAP_SIZE.y >> 1), MAP_SIZE.x, MAP_SIZE.y);
	}
}