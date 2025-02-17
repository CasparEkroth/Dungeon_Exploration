#include <SDL.h>
#include "game.h"
#include "map_maker.h"

void initGame(Game *g);

int main(){
    Game g ={0};
    MapMaker *m ={0};
    SDL_Event event;
    initGame(&g);
    while (g.isProgramnRunning){
        gameRun(&g,event);
        if(g.isMakingMap && g.pMenu->pBoolien->isDone){
            m = initMapMaker("resourses/countOfRoom.txt",g.pMap->TILE_SIZE_W,g.pMap->TILE_SIZE_H,g.pMenu->stringPlayerName);
            maker(m,&g,event);
        }
    }
    closeGame(&g);
    return 0;
}

void initGame(Game *g){
    initialize_window(g);
    g->pControls = initialize_input(); // ksk lägga dsesa i samma funktion 
    g->pControls->pCamera = initialize_camera();
    g->pMenu = initialize_Menu(g->pRenderer,g->pWindow);
    g->pMenu->pBoolien = initialize_Boolien();
    g->pMap = createMap(g->pRenderer);
    g->pPlayer = createPlayer(g->pRenderer,"Caspar",VISIBLE_WINDOW_Y*TILE_SIZE,VISIBLE_WINDOW_X*TILE_SIZE);
    printPlayer(g->pPlayer);
    g->isMakingMap =false;
    g->isProgramnRunning = true;
}