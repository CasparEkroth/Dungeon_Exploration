#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "map.h"

#define STARTING_WINDOW_WIDTH 800
#define STARTING_WINDOW_HEIGHT 600

typedef struct {
    bool game_is_runing;
    SDL_Renderer *pRenderer;
    SDL_Window *pWindow;
    Map *pMap;
}Game;

bool keys[SDL_NUM_SCANCODES] = {false};


int initialize_window(Game *pGame);
void closeGame(Game *pGame);

void gameRun(Game *pGame);


#endif 