#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "map.h"

#define STARTING_WINDOW_WIDTH 800
#define STARTING_WINDOW_HEIGHT 600

typedef struct {
    SDL_Renderer *pRenderer;
    SDL_Window *pWindow;
}Game;




int initialize_window(Game *pGame);


#endif 