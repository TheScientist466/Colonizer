#include "Game.hpp"
#include "MainMenu/MainMenu.hpp"

int main() {
	MainMenu* m = new MainMenu();
	m->Loop();

	Game* g = new Game();
	g->mainLoop();

	delete m;
	delete g;
}