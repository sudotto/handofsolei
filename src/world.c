#include <stdlib.h>
#include <stdint.h>

#include "world.h"

World new_world(int w, int h, uint8_t* map){
	World world;
	world.map = malloc(w * h); // no sizeof() bc its a 8 bit int
	for(int i = 0; i < w * h; i++){
		world.map[i] = map[i];
	}
	world.w = w;
	world.h = h;
	return world;
}

void render_world2D(Game* game, World* world){
	Img brick = new_img(game->rend, "assets/brickedup.png", 1);
	for(int y = 0; y < world->h; y++){
		for(int x = 0; x < world->w; x++){
			if(world->map[y*world->w+x] == 1){
				render_img(game->rend, &brick, x*32, y*32, 32, 32);
			} else {}
		}
	}
}
