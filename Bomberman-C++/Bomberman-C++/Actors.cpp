#include "Actors.h"


actors::player::Player::Player(SDL_Renderer* renderer) 
{
	num_life = 1;
	num_bomb = 1;
	num_score = 0;
	speed = 1;
	arrayposition = 0;
	position.x = 0;
	position.y = 0;

	int width = 32;
	int height = 32;

	texture = Texture("Bomberman_head.png", width, height, renderer);
}

actors::enemy::Enemy::Enemy(const EnemyType in_type) : type(in_type)
{
}
