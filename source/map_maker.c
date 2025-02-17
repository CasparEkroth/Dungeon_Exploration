#include "map_maker.h"
//input 
//render 
//seving to file 
void maker(MapMaker *pMapMaker, Game *pGame){
    while (pMapMaker->isMakingMap){
        if(!pMapMaker->isMakingMap) return;
        maker_input(pGame->pControls);
        maker_update(pMapMaker);
        maker_render(pGame->pRenderer,pMapMaker,pGame->pMap);
    }
    

}

void maker_render(SDL_Renderer *pRendererer,MapMaker *pMapMaker,Map *pMap){

}

void maker_update(MapMaker *pMapMaker){

}


void maker_input(ScreenAndInput *pControls){

}
