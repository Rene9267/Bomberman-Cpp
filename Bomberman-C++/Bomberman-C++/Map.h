#pragma once

#ifndef VECTOR
#include "Utility.h"
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
			Cell();/*(const CellType in_type, const BonusType in_bonus);*/
			~Cell() = default;

		private:

		};

		
	}

	class Map
	{
	public:
		std::array<map::cell_type::Cell, 256 > Mappedsize;
		Map() = delete;
		Map(const int windowSizeX, const int windowSizeY);
		~Map() = default;

	private:
		const int mapsizeX;
		const int mapsizeY;
		const int cellsize = 32;
	};

	
}

