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
    g->pCamera = initialize_camera();
    g->pMap = createMap(g->pRenderer);
}