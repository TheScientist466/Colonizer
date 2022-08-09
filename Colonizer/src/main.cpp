#include "Game.hpp"

int main() {
	Game* g = new Game();
	g->mainLoop();
	delete g;
}