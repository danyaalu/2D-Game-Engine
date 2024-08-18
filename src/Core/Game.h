#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <memory>
#include <vector>

class ColliderComponent;

class Game {
public:
	Game();
	~Game();

	void Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void Run();
	void HandleEvents();
	void Update();
	void Render();
	void Clean();

	bool running() { return isRunning; }

	static void AddTile(int id, int x, int y);
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders;

private:
	SDL_Window* window;

	int count;
	bool isRunning;
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
};