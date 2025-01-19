#include <SDL.h>
#include "game.h"

int main(){
    Game g ={0};
    SDL_Event event;
    initialize_window(&g);
    g.pMap = createMap(g.pRenderer);
    gameRun(&g,event);
    closeGame(&g);
    return 0;
}