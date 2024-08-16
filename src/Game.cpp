#include "Game.h"

SDL_Texture* playerTex;
SDL_Rect srcR, destR;

Game::Game() {}

Game::~Game() {
	Clean();
}

void Game::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN; // Set the window to fullscreen mode if requested
	}

	// Initialize SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
		isRunning = false;
		return;
	}
	std::cout << "Subsystems Initialized" << std::endl;

	// Create SDL window with specified title, position, size, and flags
	window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
	if (!window) {
		std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
		isRunning = false;
		return;
	}
	std::cout << "Window created" << std::endl;

	// Create SDL renderer for the window
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
		isRunning = false;
		return;
	}
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set window colour to white (R,G,B,A)
	std::cout << "Renderer created" << std::endl;

	// Set the running state to true if initialization is successful
	isRunning = true;

	// ---------------------------------------------------------------------------------------------------------

	// Initialising texture
	SDL_Surface* tmpSurface = IMG_Load("assets/player.png"); // Creates temporary surface to load sprite
	playerTex = SDL_CreateTextureFromSurface(renderer, tmpSurface); // Creates texture from the temporary surface

	// Frees temporary surface
	SDL_FreeSurface(tmpSurface);
}

void Game::HandleEvents() {
	// Create SDL event
	SDL_Event event;

	// Poll for currently pending events
	SDL_PollEvent(&event);

	// Handle different event types
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::Update() {
	// Update game state
	count++;
	destR.h = 64;
	destR.w = 64;
	destR.x = count;

	std::cout << count << std::endl;
}

void Game::Render() {
	// Clear renderer buffer
	SDL_RenderClear(renderer);

	// This is where we add stuff to render
	SDL_RenderCopy(renderer, playerTex, NULL, &destR); // First null renders entire image, second null draw the whole render frame

	SDL_RenderPresent(renderer);
}

void Game::Clean() {
	// Clean up resources
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "Game cleaned" << std::endl;
}

void Game::Run() {
	while (running()) {
		Uint32 frameStart = SDL_GetTicks(); // Get the start time of the frame

		HandleEvents();
		Update();
		Render();

		Uint32 frameTime = SDL_GetTicks() - frameStart; // Calculate the frame duration

		// If the frame was rendered faster than the desired frame duration, delay the next frame
		if (frameTime < frameDelay) {
			SDL_Delay(frameDelay - frameTime);
		}
	}
}