#pragma once
#include "tickable.h"
#include <string>
#include <memory>
#include <functional>
#include "Actors.h"
#include "Map.h"

#ifndef VECTOR
#include "Utility.h"
#endif // VECTOR

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

namespace game
{
	class Window
	{
	private:
		bool inputnull = false;
	protected:
		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;
		SDL_Texture* texture = nullptr;
		SDL_Texture* texture_wall = nullptr;
		map::Map* sized_map;
		bool failed = false;
		void StartFrame(bool running);
		void EndFrame();

	public:
		std::vector<actors::Actor> actor_to_renderer;
		actors::player::Player player;
		Window() = delete;
		Window(const std::string& title, const int width, const int height);
		Window(const Window& other) = delete;
		Window& operator=(const Window& other) = delete;
		~Window();
		bool IsFailed() const;
		void Run(ITickable& tickable);
		void Run(std::shared_ptr<ITickable> tickable);
		void Run(std::function<void(const float)> tick);
		void Run(std::unique_ptr<ITickable> tickable);
		void UpdatePlayerInput();
	};
}