#ifndef GAME_H
#define GAME_H
#include "menu.h"

#define SLOWNES 15


typedef struct {
    Player *pPlayer;
    ScreenAndInput *pControls;
    Menu *pMenu;
    bool game_is_running,isMakingMap,isProgramnRunning;
    SDL_Renderer *pRenderer;
    SDL_Window *pWindow;
    Map *pMap;
    //Enemy
}Game;




int initialize_window(Game *pGame);

void closeGame(Game *pGame);

void gameRun(Game *pGame,SDL_Event event);

void input(Game *pGame, SDL_Event event);
void render(Game *pGame);
void update(Game *pGame);


void worldUpdate(Game *pGame);
//void updateTileSize(SDL_Window *pWindow,Map *pMap,Menu *pMenu,Camera *pCamera);




#endif 