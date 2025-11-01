#ifndef PLAYER
#define PLAYER

#include "otto-game.h"

typedef struct {
	float x;
	float y;
	float x_vel;
	float y_vel;
	int angle;
	Img sprite;
	float spd;
} Player;

Player new_player(Game* game);
void control_player(Game* game, Player* player);
void render_player(Game* game, Player* player);

#endif
