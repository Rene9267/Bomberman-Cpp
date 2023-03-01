#pragma once
#include "SDL.h"
class Texture {
public:
	bool failed;
	SDL_Texture* texture = nullptr;

	Texture(const char* path, int width, int height, SDL_Renderer* renderer);
	Texture() = delete;
	~Texture() = default;

private:

};
