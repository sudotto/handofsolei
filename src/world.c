#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "player.h"

#include "world.h"

#define DEG_RAD 0.0174533

World new_world(int w, int h, uint8_t* map){
	World world;
	world.w = w;
	world.h = h;
	for(int y = 0; y < world.h; y++){
		for(int x = 0; x < world.w; x++){
			world.map[y][x] = map[y * world.w + x];
		}
	}
	return world;
}

void render_world2D(Game* game, World* world){
	Img brick = new_img(game->rend, "assets/brickedup.png", 1);
	for(int y = 0; y < world->h; y++){
		for(int x = 0; x < world->w; x++){
			if(world->map[y][x] == 1){
				render_img(game->rend, &brick, x*64, y*64, 64, 64);
			} else {}
		}
	}
}

void draw_rays3D(Game* game, World* world, Player* player){
	int dof;
	float ray_x, ray_y, x_offset, y_offset;
	float ray_angle = player->angle;// - DEG_RAD*30;
	int map_x, map_y;
	for(int i = 0; i < 1; i++){
		dof = 0;
		float aTan = -1/tan(ray_angle);
		if(ray_angle > M_PI){
			ray_y = (((int)player->y/64)*64)-0.0001;
			ray_x = (player->y - ray_y) * aTan + player->x;
			y_offset = -64;
			x_offset = -y_offset * aTan;
		}
		if(ray_angle < M_PI){
			ray_y = (((int)player->y/64)*64)+64;
			ray_x = (player->y - ray_y) * aTan + player->x;
			y_offset = 64;
			x_offset = -y_offset * aTan;
		}
		if(ray_angle == 0 || ray_angle == M_PI){
			ray_x = player->x;
			ray_y = player->y;
			dof = 8;
		}
		while(dof < 8){
			map_x = (int)ray_x/64;
			map_y = (int)ray_y/64;
			if(map_x >= 0 && map_x < 63 && map_y >= 0 && map_y < 63 && world->map[map_y][map_x] == 1){
				dof = 8;
			} else {
				ray_x += x_offset;
				ray_y += y_offset;
				dof += 1;
			}
		}
		float h_x = ray_x;
		float h_y = ray_y;
		float h_dist = dist(player->x - ray_x, player->y - ray_y);

		// VERTICAL LINE CHECK
		dof = 0;
		float nTan = -tan(ray_angle);
		if(ray_angle > M_PI/2 && ray_angle < (3*M_PI)/2){
			ray_x = (((int)player->x/64)*64)-0.0001;
			ray_y = (player->x - ray_x) * nTan + player->y;
			x_offset = -64;
			y_offset = -x_offset * nTan;
		}
		if(ray_angle < M_PI/2 || ray_angle > (3*M_PI)/2){
			ray_x = (((int)player->x/64)*6)+64;
			ray_y = (player->x - ray_x) * nTan + player->y;
			x_offset = 64;
			y_offset = -x_offset * nTan;
		}
		if(ray_angle == 0 || ray_angle == M_PI){
			ray_x = player->x;
			ray_y = player->y;
			dof = 8;
		}
		while(dof < 8){
			map_x = (int)ray_x/64;
			map_y = (int)ray_y/64;
			if(map_x >= 0 && map_x < 64 && map_y >= 0 && map_y < 64 && world->map[map_y][map_x] == 1){
				dof = 8;
			} else {
				ray_x += x_offset;
				ray_y += y_offset;
				dof += 1;
			}
		}
		float v_x = ray_x;
		float v_y = ray_y;
		float v_dist = dist(player->x - ray_x, player->y - ray_y);
		
		Point p1 = {player->x, player->y};
		if(h_dist <= v_dist){
			Point p2 = {(int)h_x, (int)h_y};
			draw_line(game->rend, p1, p2, 255, 0, 0, 255);
		} else {
			Point p2 = {(int)v_x, (int)v_y};
			draw_line(game->rend, p1, p2, 0, 255, 0, 255);
		}
		ray_angle += 1;
	}
}
