#include "Actors.h"
#include "Map.h"
#include "Objects.h"
#include "Window.h"

#define VECTOR
#include "Utility.h"

using tickable_vector = std::vector<std::shared_ptr<game::ITickable>>;

class MyGame : public game::ITickable
{
public:
	void Tick(const float delta_time) override
	{
		for (auto tickable : tickables)
		{
			tickable->Tick(delta_time);
		}
	}
	void AddTickables(std::shared_ptr<game::ITickable> tickable) {
		tickables.push_back(tickable);
	}
protected:
	tickable_vector tickables;
};

int main(int argc, char** argv)
{
	game::Window window("C++ addicted", 512, 512);
	auto my_game = std::make_shared<MyGame>();
	actors::player::Player pino;
	//auto actor_base = std::make_shared<game::Actor>();
	//my_game->AddTickables(actor_base);
	window.actor_to_renderer.push_back(pino);

	window.Run(my_game);
	return 0;
}

//namespace game_init {
//
//	static int Bomberman_GraficInit(SDL_Window** window, SDL_Renderer** renderer, SDL_Texture** texture)
//	{
//		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) != 0)
//		{
//			SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
//			return -1;
//		}
//
//		*window = SDL_CreateWindow("SDL is active!", 100, 100, 512, 512, 0);
//		if (!*window)
//		{
//			SDL_Log("Unable to create window: %s", SDL_GetError());
//			SDL_Quit();
//			return -1;
//		}
//
//		*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//		if (!*renderer)
//		{
//			SDL_Log("Unable to create renderer: %s", SDL_GetError());
//			SDL_DestroyWindow(*window);
//			SDL_Quit();
//			return -1;
//		}
//
//		int width;
//		int height;
//		int channels;
//		unsigned char* pixels = stbi_load("Bomberman_head.png", &width, &height, &channels, 4);
//		if (!pixels)
//		{
//			SDL_Log("Unable to open image");
//			SDL_DestroyRenderer(*renderer);
//			SDL_DestroyWindow(*window);
//			SDL_Quit();
//			return -1;
//		}
//
//		SDL_Log("Image width: %d height: %d channels: %d", width, height, channels);
//
//		*texture = SDL_CreateTexture(*renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, width, height);
//		if (!*texture)
//		{
//			SDL_Log("Unable to create texture: %s", SDL_GetError());
//			free(pixels);
//			SDL_DestroyRenderer(*renderer);
//			SDL_DestroyWindow(*window);
//			SDL_Quit();
//			return -1;
//		}
//
//		SDL_UpdateTexture(*texture, NULL, pixels, width * 4);
//		SDL_SetTextureAlphaMod(*texture, 255);
//		SDL_SetTextureBlendMode(*texture, SDL_BLENDMODE_BLEND);
//		free(pixels);
//		return 0;
//	}
// 
//	static int Bomberman_GroundCell(SDL_Window** window, SDL_Renderer** renderer, SDL_Texture** texture) {
//		int width;
//		int height;
//		int channels;
//		unsigned char* pixels = stbi_load("GroundCell.png", &width, &height, &channels, 4);
//		if (!pixels)
//		{
//			SDL_Log("Unable to open image");
//			SDL_DestroyRenderer(*renderer);
//			SDL_DestroyWindow(*window);
//			SDL_Quit();
//			return -1;
//		}
//
//		SDL_Log("Image width: %d height: %d channels: %d", width, height, channels);
//
//		*texture = SDL_CreateTexture(*renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, width, height);
//		if (!*texture)
//		{
//			SDL_Log("Unable to create texture: %s", SDL_GetError());
//			free(pixels);
//			SDL_DestroyRenderer(*renderer);
//			SDL_DestroyWindow(*window);
//			SDL_Quit();
//			return -1;
//		}
//
//		SDL_UpdateTexture(*texture, NULL, pixels, width * 4);
//		SDL_SetTextureAlphaMod(*texture, 255);
//		SDL_SetTextureBlendMode(*texture, SDL_BLENDMODE_BLEND);
//		free(pixels);
//		return 0;
//	}
//}


//int main()
//{
//	//obj_definition::cell_type::Cell map;
//	obj_definition::player::Player player;
//	obj_definition::map::Map map(512, 512);
//	int running = 1;
//	float time_delta = 0;
//	Uint32 time_prev = 0;
//	Uint32 time_curr = 0;
//	Uint32 time_frequency = SDL_GetPerformanceFrequency();
//	SDL_Window* window;
//	SDL_Renderer* renderer;
//	SDL_Texture* texture;
//	SDL_Texture* celltexture;
//	bool rightpressed = false;
//
//
//	if (game_init::Bomberman_GraficInit(&window, &renderer, &texture))
//		return -1;
//	if (game_init::Bomberman_GroundCell(&window, &renderer, &celltexture))
//		return -1;
//
//	while (running)
//	{
//		SDL_Event event;
//		while (SDL_PollEvent(&event))
//			if (event.type == SDL_QUIT)
//				running = 0;
//
//		time_prev = time_curr;
//		time_curr = SDL_GetPerformanceCounter();
//		time_delta = (time_curr - time_prev) / (float)time_frequency;
//
//		SDL_PumpEvents();
//		const Uint8* keys = SDL_GetKeyboardState(nullptr);
//		if (keys[SDL_SCANCODE_RIGHT] && !rightpressed) {
//			player.position.x += 32;
//			player.arrayposition += 16;
//			if (map.Mappedsize[player.arrayposition].type == map::cell_type::CellType::Ground) {
//				SDL_Log("giusto");
//			}
//			rightpressed = true;
//		}
//		if (keys[SDL_SCANCODE_LEFT]) {
//			player.position.x -= 32;
//			player.arrayposition -= 16;
//			if (map.Mappedsize[player.arrayposition].type == map::cell_type::CellType::Ground) {
//				SDL_Log("giusto");
//			}
//		}
//		if (keys[SDL_SCANCODE_DOWN]) {
//			player.position.y += 32;
//			player.arrayposition += 1;
//			if (map.Mappedsize[player.arrayposition].type == map::cell_type::CellType::Ground) {
//				SDL_Log("giusto");
//			}
//		}
//		if (keys[SDL_SCANCODE_UP]) {
//			player.position.y -= 32;
//			player.arrayposition -= 1;
//			if (map.Mappedsize[player.arrayposition].type == map::cell_type::CellType::Ground) {
//				SDL_Log("giusto");
//			}
//		}
//		if (keys[SDL_KEYUP]) {
//			rightpressed = false;
//		}
//
		//SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		//SDL_RenderClear(renderer);
		//SDL_Rect target_rect = { player.position.x, player.position.y, 32, 32 };
		//SDL_RenderCopy(renderer, texture, nullptr, &target_rect);
		//SDL_RenderPresent(renderer);
//	}
//	/*SDL_Rect target_rectcell = { 0 , 0, 32, 32 };
//	SDL_RenderCopy(renderer, celltexture, NULL, &target_rectcell);*/
//
//	return 0;
//}