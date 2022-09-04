#pragma once

#include "UI/Button.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

class MainMenu {

public:
	MainMenu();
	~MainMenu();

private:
	sf::RenderWindow* mWindow;
	sf::Event mEvents;

	std::vector<Button<MainMenu>*> Buttons;

public:
	void Loop();

private:
	static void clk1(Button<MainMenu>&, MainMenu&);
};