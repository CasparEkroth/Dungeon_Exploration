#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "map.h"

#define STARTING_WINDOW_WIDTH (TILE_SIZE*20)
#define STARTING_WINDOW_HEIGHT (TILE_SIZE*15)

typedef struct {
    Uint32 currentTime;
    Uint32 previousTime;
    bool keys[SDL_NUM_SCANCODES];
    int deltaTimeResize;
}ScreenAndInput;

typedef struct {
    ScreenAndInput *pControls;
    bool game_is_running;
    SDL_Renderer *pRenderer;
    SDL_Window *pWindow;
    Map *pMap;
}Game;




int initialize_window(Game *pGame);
ScreenAndInput* initialize_input(void);
void closeGame(Game *pGame);

void gameRun(Game *pGame,SDL_Event event);
void input(Game *pGame, SDL_Event event);
void render(Game *pGame);
void updateTileSize(Game *pGame);



#endif 