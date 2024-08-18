#include "Core/Game.h"

Game* game = nullptr;

int main(int argc, char* argv[]) {
	game = new Game;

	game->Init("2D SDL Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 960, false);

	game->Run();

	// Delete the game object to free heap memory
	delete game;

	return 0;
}