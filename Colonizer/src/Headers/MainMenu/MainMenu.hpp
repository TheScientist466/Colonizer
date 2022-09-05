#pragma once

#include "UI/Button.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

struct MainMenu {
	MainMenu();
	~MainMenu();

	sf::RenderWindow* mWindow;
	sf::Event mEvents;

	std::vector<Button<MainMenu>*> MainButtons;
	std::vector<Button<MainMenu>*> OptionButtons;

	std::vector<Button<MainMenu>*>* toWorkPtr;

	void Loop();
	bool toStartGame;
};

namespace ButtonActions {
	void startGame(Button<MainMenu>&, MainMenu&);
	void quit(Button<MainMenu>&, MainMenu&);
	void goToOptions(Button<MainMenu>&, MainMenu&);

	void comeBackFromOptions(Button<MainMenu>&, MainMenu&);
	void setRes(Button<MainMenu>&, MainMenu&);
	void fullScreen(Button<MainMenu>&, MainMenu&);
}