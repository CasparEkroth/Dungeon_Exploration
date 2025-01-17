#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "map.h"

#define STARTING_WINDOW_WIDTH 800
#define STARTING_WINDOW_HEIGHT 600

typedef struct {
    bool keys[SDL_NUM_SCANCODES];
    bool game_is_running;
    SDL_Renderer *pRenderer;
    SDL_Window *pWindow;
    Map *pMap;
}Game;

int initialize_window(Game *pGame);
void closeGame(Game *pGame);

void gameRun(Game *pGame,SDL_Event event);
void input(Game *pGame, SDL_Event event);



#endif 