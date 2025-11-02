#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3_image/SDL_image.h>

#include "otto-game.h"

#include "player.h"

Player new_player(Game* game){
	Player player;
	player.x = 0;
	player.y = 0;
	player.x_vel = 0;
	player.y_vel = 0;
	player.angle = 0;
	player.spd = 10;
	player.sprite = new_img(game->rend, "assets/player/debug.png", 1);
	return player;
}

void control_player(Game* game, Player* player){
	float local_y_axis = player->angle * (M_PI / 180.0);
	float local_x_axis = (player->angle + 90) * (M_PI / 180.0);
	if(game->keystates[SDL_SCANCODE_W]){
		player->x_vel += cos(local_y_axis);
		player->y_vel += sin(local_y_axis);
	}
	if(game->keystates[SDL_SCANCODE_A]){
		player->x_vel -= cos(local_x_axis);
		player->y_vel -= sin(local_x_axis);
	}
	if(game->keystates[SDL_SCANCODE_S]){
		player->x_vel -= cos(local_y_axis);
		player->y_vel -= sin(local_y_axis);
	}
	if(game->keystates[SDL_SCANCODE_D]){
		player->x_vel += cos(local_x_axis);
		player->y_vel += sin(local_x_axis);
	}
	if(game->keystates[SDL_SCANCODE_K]){
		player->angle -= 1;
		if(player->angle < 0){
			player->angle = 360;
		}
	}
	if(game->keystates[SDL_SCANCODE_L]){
		player->angle += 1;
		if(player->angle > 360){
			player->angle = 0;
		}
	}
	player->x += player->x_vel;
	player->y += player->y_vel;

	if(player->x_vel < -1){
		player->x_vel += 1;
	}
	if(player->x_vel > 1){
		player->x_vel -= 1;
	}
	if(player->y_vel < -1){
		player->y_vel += 1;
	}
	if(player->y_vel > 1){
		player->y_vel -= 1;
	}
	if(player->x_vel >= -1 && player->x_vel <= 1){
		player->x_vel = 0;
	}
	if(player->y_vel >= -1 && player->y_vel <= 1){
		player->y_vel = 0;
	}
}

void render_player(Game* game, Player* player){
	rotate_img(&player->sprite, player->angle);
	render_img(game->rend, &player->sprite, player->x, player->y, 32, 32);
}
