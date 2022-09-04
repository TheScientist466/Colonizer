#include "MainMenu/MainMenu.hpp"

MainMenu::MainMenu() {
	mWindow = new sf::RenderWindow(sf::VideoMode(800, 600), "Colonizer - Main Menu", sf::Style::Close, sf::ContextSettings(0, 0, 3));
	mWindow->setFramerateLimit(30);
	toStartGame = false;

	Button<MainMenu>* startButton = new Button<MainMenu>(sf::FloatRect(26, 195, 250, 50), this, nullptr, &ButtonActions::startGame);
	startButton->text.setString("Start");
	Buttons.push_back(startButton);

	Button<MainMenu>* optionsButton = new Button<MainMenu>(sf::FloatRect(26, 275, 250, 50), this, nullptr, nullptr);
	optionsButton->text.setString("Options");
	Buttons.push_back(optionsButton);

	Button<MainMenu>* quitButton = new Button<MainMenu>(sf::FloatRect(26, 355, 250, 50), this, nullptr, &ButtonActions::quit);
	quitButton->text.setString("Quit");
	Buttons.push_back(quitButton);

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

void ButtonActions::startGame(Button<MainMenu>& b, MainMenu& m) {
	m.mWindow->close();
	m.toStartGame = true;
}

void ButtonActions::quit(Button<MainMenu>& b, MainMenu& m) {
	m.mWindow->close();
}
