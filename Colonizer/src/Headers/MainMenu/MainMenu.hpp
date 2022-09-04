#pragma once

#include "UI/Button.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

struct MainMenu {
	MainMenu();
	~MainMenu();

	sf::RenderWindow* mWindow;
	sf::Event mEvents;

	std::vector<Button<MainMenu>*> Buttons;

	void Loop();
	bool toStartGame;
};

namespace ButtonActions {
	void startGame(Button<MainMenu>&, MainMenu&);
	void quit(Button<MainMenu>&, MainMenu&);
}