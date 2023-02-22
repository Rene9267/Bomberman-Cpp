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

	int pixel_width = 32;
	int pixel_height = 32;
	int channels;
	unsigned char* pixels = stbi_load("Bomberman_head.png", &pixel_width, &pixel_height, &channels, 4);
	if (!pixels)
	{
		SDL_Log("Unable to open image");
		failed = true;
		return;
	}

	SDL_Log("Image width: %d height: %d channels: %d", pixel_width, pixel_width, channels);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, pixel_width, pixel_height);
	if (!texture)
	{
		SDL_Log("Unable to create texture: %s", SDL_GetError());
		free(pixels);
		failed = true;
		return;
	}

	int pixel_width_2 = 64;
	int pixel_height_2;
	int channels_2;
	unsigned char* pixels_2 = stbi_load("Wall.png", &pixel_width_2, &pixel_height_2, &channels_2, 3);
	if (!pixels_2)
	{
		SDL_Log("Unable to open image");
		failed = true;
		return;
	}

	SDL_Log("Image width: %d height: %d channels: %d", pixel_width_2, pixel_height_2, channels_2);

	texture_wall = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, pixel_width, pixel_height);
	if (!texture_wall)
	{
		SDL_Log("Unable to create texture: %s", SDL_GetError());
		free(pixels_2);
		failed = true;
		return;
	}

	SDL_UpdateTexture(texture, NULL, pixels, pixel_width * 4);
	SDL_SetTextureAlphaMod(texture, 255);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

	SDL_UpdateTexture(texture_wall, NULL, pixels_2, pixel_width_2);

	free(pixels);
	free(pixels_2);

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

void game::Window::UpdatePlayerInput() {
	SDL_PumpEvents();
	const Uint8* keys = SDL_GetKeyboardState(nullptr);

	if (keys[SDL_SCANCODE_RIGHT] && !inputnull) {
		inputnull = true;
		player.arrayposition += 16;
		if (player.arrayposition < (*sized_map).Mappedsize.size() && (*sized_map).Mappedsize[player.arrayposition].type == map::cell_type::CellType::Ground)
			player.position.x += 32;
		else
			player.arrayposition -= 16;
	}
	if (keys[SDL_SCANCODE_LEFT] && !inputnull) {
		inputnull = true;
		player.arrayposition -= 16;
		if (player.arrayposition > 0 && (*sized_map).Mappedsize[player.arrayposition].type == map::cell_type::CellType::Ground)
			player.position.x -= 32;
		else
			player.arrayposition += 16;
	}
	if (keys[SDL_SCANCODE_DOWN] && !inputnull) {
		inputnull = true;
		player.arrayposition += 1;
		if (player.arrayposition < (*sized_map).Mappedsize.size() && (*sized_map).Mappedsize[player.arrayposition].type == map::cell_type::CellType::Ground)
			player.position.y += 32;
		else
			player.arrayposition -= 1;
	}
	if (keys[SDL_SCANCODE_UP] && !inputnull) {
		inputnull = true;
		player.arrayposition -= 1;
		if (player.arrayposition > 0 && (*sized_map).Mappedsize[player.arrayposition].type == map::cell_type::CellType::Ground && player.arrayposition >= 0)
			player.position.y -= 32;
		else
			player.arrayposition += 1;
	}

}

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