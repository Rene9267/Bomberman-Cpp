#include "Window.h"
#include "SDL.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

game::Window::Window(const std::string& title, const int width, const int height)
{
	sized_map = new map::Map(width, height);
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		failed = true;
		return;
	}

	window = SDL_CreateWindow(title.c_str(), 100, 100, width, height, 0);
	if (!window)
	{
		SDL_Log("Unable to create window: %s", SDL_GetError());
		failed = true;
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
	{
		SDL_Log("Unable to create renderer: %s", SDL_GetError());
		failed = true;
		return;
	}

	

	return;
}

bool game::Window::IsFailed() const
{
	return failed;
}

void game::Window::Run(ITickable& tickable)
{
	bool running = true;
	while (running)
	{
		StartFrame(running);
		tickable.Tick(1.f / 60.f);
		EndFrame();
	}
}

void game::Window::Run(std::shared_ptr<ITickable> tickable)
{
	//Run(std::bind(&game::ITickable::Tick, tickable.get(), 1.f/60.f));
	Run(*tickable.get());
}

void game::Window::Run(std::unique_ptr<ITickable> tickable)
{
	//Run(std::bind(&game::ITickable::Tick, tickable.get(), 1.f/60.f));
	Run(*tickable.get());
}

void game::Window::StartFrame(bool running) {
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			running = false;
		}
		if (event.type == SDL_KEYUP) {
			inputnull = false;
		}
	}
}
//
//void game::Window::UpdatePlayerInput() {
//	SDL_PumpEvents();
//	const Uint8* keys = SDL_GetKeyboardState(nullptr);
//
//	if (keys[SDL_SCANCODE_RIGHT] && !inputnull) {
//		inputnull = true;
//		player.arrayposition += 16;
//		if (player.arrayposition < (*sized_map).Mappedsize.size() && (*sized_map).Mappedsize[player.arrayposition].type == map::cell_type::CellType::Ground)
//			player.position.x += 32;
//		else
//			player.arrayposition -= 16;
//	}
//	if (keys[SDL_SCANCODE_LEFT] && !inputnull) {
//		inputnull = true;
//		player.arrayposition -= 16;
//		if (player.arrayposition > 0 && (*sized_map).Mappedsize[player.arrayposition].type == map::cell_type::CellType::Ground)
//			player.position.x -= 32;
//		else
//			player.arrayposition += 16;
//	}
//	if (keys[SDL_SCANCODE_DOWN] && !inputnull) {
//		inputnull = true;
//		player.arrayposition += 1;
//		if (player.arrayposition < (*sized_map).Mappedsize.size() && (*sized_map).Mappedsize[player.arrayposition].type == map::cell_type::CellType::Ground)
//			player.position.y += 32;
//		else
//			player.arrayposition -= 1;
//	}
//	if (keys[SDL_SCANCODE_UP] && !inputnull) {
//		inputnull = true;
//		player.arrayposition -= 1;
//		if (player.arrayposition > 0 && (*sized_map).Mappedsize[player.arrayposition].type == map::cell_type::CellType::Ground && player.arrayposition >= 0)
//			player.position.y -= 32;
//		else
//			player.arrayposition += 1;
//	}
//
//}

void game::Window::EndFrame() {
	UpdatePlayerInput();
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderClear(renderer);
	for (const auto actor : sized_map->Mappedsize)
	{
		if (actor.type == map::cell_type::CellType::Wall) {
			SDL_Rect target_rect = { actor.position.x, actor.position.y, 32, 32 };
			SDL_RenderCopy(renderer, texture_wall, nullptr, &target_rect);
		}
	}
	SDL_Rect target_rect_player = { player.position.x, player.position.y, 32, 32 };
	SDL_RenderCopy(renderer, texture, nullptr, &target_rect_player);
	SDL_RenderPresent(renderer);
}

void game::Window::Run(std::function<void(const float)> tick)
{
	bool running = true;
	while (running)
	{
		StartFrame(running);
		tick(1.f / 60.f);
		EndFrame();
	}
}

game::Window::~Window()
{
	if (renderer)
	{
		SDL_DestroyRenderer(renderer);
	}
	if (window)
	{
		SDL_DestroyWindow(window);
	}
	if (SDL_WasInit(0) != 0)
	{
		SDL_Quit();
	}
}