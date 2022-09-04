#include "MainMenu/MainMenu.hpp"

MainMenu::MainMenu() {
	mWindow = new sf::RenderWindow(sf::VideoMode(800, 600), "Colonizer - Main Menu", sf::Style::Close);
	mWindow->setFramerateLimit(30);

	Button<MainMenu>* b = new Button<MainMenu>(sf::FloatRect(20, 450, 400, 100), this, nullptr, &clk1);
	b->text.setString("Start");
	Buttons.push_back(b);
}

MainMenu::~MainMenu() {
	for(auto& a : Buttons)
		delete a;

	delete mWindow;
}

void MainMenu::Loop() {
	while(mWindow->isOpen()) {
		while(mWindow->pollEvent(mEvents)) {
			switch(mEvents.type) {
				case sf::Event::Closed:
					mWindow->close();
					break;
				case sf::Event::MouseButtonPressed:
					if(mEvents.mouseButton.button == sf::Mouse::Button::Left)
						for(auto a : Buttons) {
							if(!a->isClicked) {
								if(a->getHitbox().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*mWindow)))) {
									a->Click();
								}
							}
						}
					break;
				case sf::Event::MouseButtonReleased:
					if(mEvents.mouseButton.button == sf::Mouse::Button::Left) {
						for(auto a : Buttons) {
							if(a->isClicked) {
								a->Release();
							}
						}
					}
					break;
			}
		}
		mWindow->clear();
		for(auto& a : Buttons) {
			mWindow->draw(*(a->getShape()));
			mWindow->draw(a->text);
		}
		mWindow->display();
	}
}

void MainMenu::clk1(Button<MainMenu>& b, MainMenu& m) {
	m.mWindow->close();
}
