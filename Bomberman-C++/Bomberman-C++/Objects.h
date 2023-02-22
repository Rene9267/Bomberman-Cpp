#pragma once

#ifndef VECTOR
#include "Utility.h"
#endif // VECTOR


namespace objects {

	namespace bomb {
		class Bomb
		{
		public:
			collections::Vector2 position;
			unsigned int range = 0;
			unsigned int cooldown = 0;
			Bomb();
			~Bomb() = default;

		private:

		};

		

		
	}
}

