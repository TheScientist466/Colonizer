#include "MainMenu/MainMenu.hpp"
#include "constants.hpp"

MainMenu::MainMenu() {
	mWindow = new sf::RenderWindow(sf::VideoMode(800, 600), "Colonizer - Main Menu", sf::Style::Close, sf::ContextSettings(0, 0, 3));
	mWindow->setFramerateLimit(30);
	toStartGame = false;

	toWorkPtr = &MainButtons;

	Button<MainMenu>* startButton = new Button<MainMenu>(sf::FloatRect(26, 195, 250, 50), this, nullptr, &ButtonActions::startGame);
	startButton->text.setString("Start");
	MainButtons.push_back(startButton);

	Button<MainMenu>* optionsButton = new Button<MainMenu>(sf::FloatRect(26, 275, 250, 50), this, nullptr, &ButtonActions::goToOptions);
	optionsButton->text.setString("Options");
	MainButtons.push_back(optionsButton);

	Button<MainMenu>* quitButton = new Button<MainMenu>(sf::FloatRect(26, 355, 250, 50), this, nullptr, &ButtonActions::quit);
	quitButton->text.setString("Quit");
	MainButtons.push_back(quitButton);

	Button<MainMenu>* backButton = new Button<MainMenu>(sf::FloatRect(10, 565, 250, 25), this, nullptr, &ButtonActions::comeBackFromOptions);
	backButton->text.setCharacterSize(20);
	backButton->text.setString("Back");
	OptionButtons.push_back(backButton);

	Button<MainMenu>* resButton1 = new Button<MainMenu>(sf::FloatRect(510, 177, 250, 25), this, nullptr, &ButtonActions::setRes);
	resButton1->text.setCharacterSize(20);
	resButton1->text.setString("1024x576");
	resButton1->id = 1;
	OptionButtons.push_back(resButton1);

	Button<MainMenu>* resButton2 = new Button<MainMenu>(sf::FloatRect(510, 232, 250, 25), this, nullptr, &ButtonActions::setRes);
	resButton2->text.setCharacterSize(20);
	resButton2->text.setString("1280x720");
	resButton2->id = 2;
	OptionButtons.push_back(resButton2);

	Button<MainMenu>* resButton3 = new Button<MainMenu>(sf::FloatRect(510, 287, 250, 25), this, nullptr, &ButtonActions::setRes);
	resButton3->text.setCharacterSize(20);
	resButton3->text.setString("1366x768");
	resButton3->id = 3;
	OptionButtons.push_back(resButton3);

	Button<MainMenu>* resButton4 = new Button<MainMenu>(sf::FloatRect(510, 342, 250, 25), this, nullptr, &ButtonActions::setRes);
	resButton4->text.setCharacterSize(20);
	resButton4->text.setString("1600x900");
	resButton4->id = 4;
	OptionButtons.push_back(resButton4);

	Button<MainMenu>* resButton5 = new Button<MainMenu>(sf::FloatRect(510, 397, 250, 25), this, nullptr, &ButtonActions::setRes);
	resButton5->text.setCharacterSize(20);
	resButton5->text.setString("1920x1080");
	resButton5->id = 5;
	OptionButtons.push_back(resButton5);

	Button<MainMenu>* resButton6 = new Button<MainMenu>(sf::FloatRect(510, 565, 250, 25), this, nullptr, &ButtonActions::fullScreen);
	resButton6->text.setCharacterSize(20);
	resButton6->text.setString("FullScreen");
	resButton6->id = 5;
	OptionButtons.push_back(resButton6);
}

MainMenu::~MainMenu() {
	for(auto& a : MainButtons)
		delete a;
	for(auto& a : OptionButtons)
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
						for(auto a : *toWorkPtr) {
							if(!a->isClicked) {
								if(a->getHitbox().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*mWindow)))) {
									a->Click();
								}
							}
						}
					break;
				case sf::Event::MouseButtonReleased:
					if(mEvents.mouseButton.button == sf::Mouse::Button::Left) {
						for(auto a : *toWorkPtr) {
							if(a->isClicked) {
								a->Release();
							}
						}
					}
					break;
			}
		}
		mWindow->clear();
		for(auto& a : *toWorkPtr) {
			mWindow->draw(*a);
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

void ButtonActions::goToOptions(Button<MainMenu>& b, MainMenu& m) {
	m.toWorkPtr = &m.OptionButtons;
}

void ButtonActions::comeBackFromOptions(Button<MainMenu>& b, MainMenu& m) {
	m.toWorkPtr = &m.MainButtons;
}

void ButtonActions::setRes(Button<MainMenu>& b, MainMenu& m) {
	switch(b.id) {
		case 1:
			config::window::WINDOW_DIMENTIONS = sf::Vector2i(1024, 576);
			break;
		case 2:
			config::window::WINDOW_DIMENTIONS = sf::Vector2i(1280, 720);
			break;
		case 3:
			config::window::WINDOW_DIMENTIONS = sf::Vector2i(1366, 768);
			break;
		case 4:
			config::window::WINDOW_DIMENTIONS = sf::Vector2i(1600, 900);
			break;
		case 5:
			config::window::WINDOW_DIMENTIONS = sf::Vector2i(1920, 1080);
			break;
	}
}

void ButtonActions::fullScreen(Button<MainMenu>& b, MainMenu& m) {
	config::window::TO_FULLSCREEN ^= 1;
}