#ifndef GAME_H
#define GAME_H
#include "menu.h"

#define STARTING_WINDOW_WIDTH (TILE_SIZE*20)
#define STARTING_WINDOW_HEIGHT (TILE_SIZE*15)

#define SLOWNES 15



typedef struct {
    SDL_Point Ofset,curentPos;
}Camera;


typedef struct {
    Player *pPlayer;
    Camera *pCamera;
    ScreenAndInput *pControls;
    Menu *pMenu;
    bool game_is_running;
    SDL_Renderer *pRenderer;
    SDL_Window *pWindow;
    Map *pMap;
    //Enemy
}Game;




int initialize_window(Game *pGame);
Camera *initialize_camera(void);

void closeGame(Game *pGame);

void gameRun(Game *pGame,SDL_Event event);

void input(Game *pGame, SDL_Event event);
void render(Game *pGame);
void update(Game *pGame);


void worldUpdate(Game *pGame);
void updateTileSize(Game *pGame);



#endif 