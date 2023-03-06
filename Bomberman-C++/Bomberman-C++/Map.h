#pragma once

#ifndef VECTOR
#include "Utility.h"
#include "Texture.h"
#endif // VECTOR

namespace map {

	namespace cell_type {

		enum class CellType {
			Ground = 0, Wall, UndestroyableWall, Teleport
		};
		enum class BonusType {
			None = 0, Speed, BombX2, BombX3
		};

		class Cell
		{
		public:
			collections::Vector2 position;
			CellType type;
			BonusType bonus;
			Texture texture;
			void Cell_init(SDL_Renderer* renderer);/*(const CellType in_type, const BonusType in_bonus);*/
			~Cell() = default;
			Cell() = default;
		private:

		};

	}

	class Map
	{
	public:
		std::array<map::cell_type::Cell, 256 > Mappedsize;
		Map() = delete;
		Map(const int windowSizeX, const int windowSizeY, SDL_Renderer* renderer);
		~Map() = default;

	private:
		const int mapsizeX;
		const int mapsizeY;
		const int cellsize = 32;
	};


}

