#include <stdio.h>
#include <stdbool.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3_image/SDL_image.h>

#include "otto-game.h"

int main(int argc, char* argv[]){
	Game game = new_game("Hand Of Solei", 900, 600);
	while(game.running){
		game.frame_start = SDL_GetTicks();
		clear_game(&game, 0, 0, 0);

		while(get_game_events(&game)){
			switch(game.event.type){
				case SDL_EVENT_QUIT:
					game.running = false;
					break;
			}
		}

		render_game_cursor(&game, 32, 32);
		update_game(&game);
		cap_game_framerate(&game, 60);
	}
	destroy_game(&game);
}
