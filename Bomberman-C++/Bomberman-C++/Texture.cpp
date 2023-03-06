#pragma once
#include "Texture.h"

Texture::Texture(const char* path, int width, int height, SDL_Renderer* renderer) {
	int channels;
	unsigned char* pixels = stbi_load("Bomberman_head.png", &width, &height, &channels, 4);
	if (!pixels) {
		SDL_Log("Unable to open image");
		failed = true;
		return;
	}

	SDL_Log("Image width: %d height: %d channels: %d", width, height, channels);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, width, height);
	if (!texture) {
		SDL_Log("Unable to create texture: %s", SDL_GetError());
		free(pixels);
		failed = true;
		return;
	}

	/*int pixel_width_2 = 64;
	int pixel_height_2;
	int channels_2;
	unsigned char* pixels_2 = stbi_load("Wall.png", &pixel_width_2, &pixel_height_2, &channels_2, 4);
	if (!pixels_2) {
		SDL_Log("Unable to open image");
		failed = true;
		return;
	}

	SDL_Log("Image width: %d height: %d channels: %d", pixel_width_2, pixel_height_2, channels_2);*/

	/*texture_wall = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, width, height);
	if (!texture_wall) {
		SDL_Log("Unable to create texture: %s", SDL_GetError());
		free(pixels_2);
		failed = true;
		return;
	}*/

	SDL_UpdateTexture(texture, NULL, pixels, width * 4);
	SDL_SetTextureAlphaMod(texture, 255);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

	/*SDL_UpdateTexture(texture_wall, NULL, pixels_2, pixel_width_2);*/

	free(pixels);
	//free(pixels_2);
}