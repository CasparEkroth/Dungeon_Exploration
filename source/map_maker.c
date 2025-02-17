#include "map_maker.h"
//input 
//render 
//seving to file 
MapMaker* initMapMaker(char fileName[NAME],int tileSizeW,int tileSizeH, char oldMap[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X]){
    MapMaker* pMapMaker = malloc(sizeof(MapMaker));
    if(!pMapMaker){
        fprintf(stderr,"Erorr alocating memory for MapMaker\n");
        return NULL;
    }
    pMapMaker->isChosingNewTile = false;
    pMapMaker->isMakingMap = false;
    pMapMaker->isSavede = false;
    strcpy(pMapMaker->fileName,fileName);
    for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++){
        for (int x = 0; x < NUMMBER_OF_TILSE_X; x++){
            pMapMaker->rect_map[y][x].w = tileSizeW;
            pMapMaker->rect_map[y][x].h = tileSizeH;
            pMapMaker->rect_map[y][x].y = (tileSizeH*y);
            pMapMaker->rect_map[y][x].x = (tileSizeW*x);
            pMapMaker->map[y][x] = oldMap[y][x];
        }
        
    }
    pMapMaker->selectedTile = ' ';
    return pMapMaker;
} 


void maker(MapMaker *pMapMaker, Game *pGame,SDL_Event event){
    while (pMapMaker->isMakingMap){
        if(!pMapMaker->isMakingMap) return;
        maker_input(pGame->pControls,event);
        maker_update(pMapMaker);
        maker_render(pGame->pRenderer,pMapMaker,pGame->pMap);
    }
    

}

void maker_render(SDL_Renderer *pRendererer,MapMaker *pMapMaker,Map *pMap){
    renderMap(pRendererer,pMapMaker->map,pMap->tileIndex,pMap->pTileShet,pMapMaker->rect_map);
}

void maker_update(MapMaker *pMapMaker){

}


void maker_input(ScreenAndInput *pControls,SDL_Event event){

}
