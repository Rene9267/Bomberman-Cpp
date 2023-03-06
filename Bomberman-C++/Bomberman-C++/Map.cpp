#include "Map.h"

map::Map::Map(const int windowSizeX, const int windowSizeY, SDL_Renderer* renderer) : mapsizeX(windowSizeX), mapsizeY(windowSizeY)
{
	auto xcycle = windowSizeX / cellsize;
	auto ycycle = windowSizeY / cellsize;
	auto yoffset = 0;
	auto xoffset = 0;

	for (int x = 0; x < xcycle; x++)
	{
		for (int y = 0; y < ycycle; y++)
		{
			Mappedsize[y + (xcycle * x)].Cell_init(renderer);
			Mappedsize[y + (xcycle * x)].position.x = xoffset;
			Mappedsize[y + (xcycle * x)].position.y = yoffset;
			Mappedsize[y + (xcycle * x)].type = cell_type::CellType::Ground;
			Mappedsize[y + (xcycle * x)].bonus = cell_type::BonusType::None;
			if (y % 3 == 0 && y != 0 && x % 2 == 0) {
				Mappedsize[y + (xcycle * x)].type = cell_type::CellType::Wall;
				Mappedsize[y + (xcycle * x)].bonus = cell_type::BonusType::None;
			}
			yoffset += cellsize;
		}
		yoffset = 0;
		xoffset += cellsize;
	}
}

void map::cell_type::Cell::Cell_init(SDL_Renderer* renderer)/*(const CellType in_type, const BonusType in_bonus) : type(in_type), bonus(in_bonus)*/
{
	type = CellType::Ground;
	bonus = BonusType::None;

	int width = 32;
	int height = 32;

	texture = Texture("Wall.png", width, height, renderer);
}