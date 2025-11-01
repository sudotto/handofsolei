#ifndef WORLD
#define WORLD

#include <stdint.h>

#include "otto-game.h"

typedef struct {
	uint8_t* map;
	int w;
	int h;
} World;

World new_world(int w, int h, uint8_t* map);
void render_world2D(Game* game, World* world);

#endif
