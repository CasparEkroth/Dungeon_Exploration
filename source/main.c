#include <SDL.h>
#include "game.h"

void initGame(Game *g);

int main(){
    Game g ={0};
    SDL_Event event;
    initGame(&g);
    gameRun(&g,event);
    closeGame(&g);
    return 0;
}

void initGame(Game *g){
    initialize_window(g);
    g->pControls = initialize_input(); // ksk lägga dsesa i samma funktion 
    g->pControls->pCamera = initialize_camera();
    g->pMenu = initialize_Menu(g->pRenderer,g->pWindow);
    g->pMap = createMap(g->pRenderer);
    g->pPlayer = createPlayer(g->pRenderer,"Caspar",VISIBLE_WINDOW_Y*TILE_SIZE,VISIBLE_WINDOW_X*TILE_SIZE);
    printPlayer(g->pPlayer);
}