#pragma once
#ifndef VECTOR
#include "SDL.h"
#include "stb_image.h"
#endif // VECTOR


struct SDL_Texture;
struct SDL_Renderer;

class Texture {
public:
	bool failed = false;
	SDL_Texture* texture = nullptr;

	Texture(const char* path, int width, int height, SDL_Renderer* renderer);
	Texture() = default;
	~Texture() = default;

private:

};
