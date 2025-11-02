#ifndef WORLD
#define WORLD

#include <stdint.h>

#include "otto-game.h"
#include "player.h"

#define MAX_WORLD_SIZE 64

typedef struct {
	uint8_t map[MAX_WORLD_SIZE][MAX_WORLD_SIZE];
	int w;
	int h;
} World;

World new_world(int w, int h, uint8_t* map);
void render_world2D(Game* game, World* world);
void draw_rays3D(Game* game, World* world, Player* player);

#endif
