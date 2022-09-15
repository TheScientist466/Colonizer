#include "MainMenu/Loader.hpp"

#include <iostream>

sf::Vector2i config::window::WINDOW_DIMENTIONS = sf::Vector2i(1600, 900);
bool config::window::TO_FULLSCREEN = false;

std::string config::window::WINDOW_TITLE = "yay";

Loader::Loader() {

	auto a = sf::VideoMode::getDesktopMode();

	std::cout << a.width << ", " << a.height << ", " << a.bitsPerPixel << std::endl;

}