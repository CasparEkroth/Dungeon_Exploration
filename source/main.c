#include <SDL.h>
#include "game.h"




int main(){
    Game g ={0};
    SDL_Event event;
    gameRun(&g);
    closeGame(&g);
    return 0;
}