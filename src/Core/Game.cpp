#include "Game.h"
#include "../Managers/TextureManager.h"
#include "../Maps/Map.h"
#include "../Utilities/Collision.h"
#include "ECS.h"
#include "../Components/Components.h"

Map* map;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
EntityManager manager;

std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.AddEntity());
auto& wall(manager.AddEntity());

auto& tile0(manager.AddEntity());
auto& tile1(manager.AddEntity());
auto& tile2(manager.AddEntity());

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

	map = new Map();

	// ECS Implementation

	tile0.addComponent<TileComponent>(200, 200, 32, 32, 1);

	tile1.addComponent<TileComponent>(250, 250, 32, 32, 0);
	tile1.addComponent<ColliderComponent>("water");

	tile2.addComponent<TileComponent>(150, 150, 32, 32, 2);
	tile2.addComponent<ColliderComponent>("grass");

	player.addComponent<TransformComponent>(2); // To set position, add x and y parameters
	player.addComponent<SpriteComponent>("assets/images/Dirt.png");
	player.addComponent<KeyboardComponent>();
	player.addComponent<ColliderComponent>("player");

	wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent<SpriteComponent>("assets/images/Dirt.png");
	wall.addComponent<ColliderComponent>("wall");
}

void Game::HandleEvents() {
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
	manager.Refresh();
	manager.Update();

	// Loop through all colliders and check for collisions
	for (auto cc : colliders) {
		Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
	}
}

void Game::Render() {
	// Clear renderer buffer
	SDL_RenderClear(renderer);

	// This is where we add stuff to render
	//map->DrawMap();

	manager.Draw();

	SDL_RenderPresent(renderer);
}

void Game::Clean() {
	// Clean up resources
	SDL_DestroyWindow(window);
	std::cout << "Destroyed SDL window" << std::endl;
	SDL_DestroyRenderer(renderer);
	std::cout << "Destroyed SDL renderer" << std::endl;
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