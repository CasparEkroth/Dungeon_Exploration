#ifndef MAP_MAKER_H
#define MAP_MAKER_H
#include "game.h"


typedef struct {
    char selectedTile;
    char fileName[NAME];
    char map[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X];
    SDL_Rect rect_map[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X];
    bool isSavede,isChosingNewTile,isMakingMap;
}MapMaker;

MapMaker* initMapMaker(char fileName[NAME],int tileSizeW,int tileSizeH, char oldMap[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X]);

void maker(MapMaker *pMapMaker, Game *pGame,SDL_Event event);
void maker_input(ScreenAndInput *pControls,SDL_Event event);
void maker_update(MapMaker *pMapMaker);
void maker_render(SDL_Renderer *pRendererer,MapMaker *pMapMaker,Map *pMap);


#endif

// det kommer att var en selekt funktion där man sedan plaserar ut de 
// tiles man vill och därefter väljer en till 