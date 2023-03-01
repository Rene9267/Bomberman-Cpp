#pragma once
#include "Texture.h"
#ifndef VECTOR
#include "Utility.h"
#endif // VECTOR

namespace actors {

	class Actor
	{
	public:
		collections::Vector2 position;
		Texture texture;
		Actor() = default;
		~Actor() = default;
	};

	namespace enemy {
		enum class EnemyType {
			Bat, Balloon
		};

		class Enemy : public Actor
		{
		public:
			EnemyType type;
			Enemy(const EnemyType in_type);
			~Enemy() = default;

		private:
		};
	}
	
	namespace player {
		class Player: public Actor
		{
		public:
			unsigned int num_life;
			unsigned int num_bomb;
			unsigned int num_score;
			unsigned int speed;
			int arrayposition;
			Player(SDL_Renderer* renderer);
			Player() = delete;
			~Player() = default;
		};
	}
}

