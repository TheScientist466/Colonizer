#include "Game.hpp"
#include "MainMenu/MainMenu.hpp"

int main() {
	MainMenu* m = new MainMenu();
	m->Loop();
	if(m->toStartGame) {
		Game* g = new Game();
		g->mainLoop();
		delete g;
	}
	delete m;
}