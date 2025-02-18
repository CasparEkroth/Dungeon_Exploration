#ifndef MAP_MAKER_H
#define MAP_MAKER_H
#include "game.h"

#define SPEED (32)

typedef struct {
    char selectedTile;
    SDL_Point highlight_rect;
    SDL_Point mapOfset;
    char fileName[NAME];
    char romeName[NAME];
    char map[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X];
    SDL_Rect rect_map[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X];
    bool isSavede,isChosingNewTile,isMakingMap;
    bool keys[SDL_NUM_SCANCODES];
}MapMaker;

MapMaker* initMapMaker(char fileName[NAME],int tileSizeW,int tileSizeH,char romeName[NAME]);

bool isOnListofRom(char fileName[NAME],char romName[NAME]);


void maker(MapMaker *pMapMaker, Game *pGame,bool *isGameRunnig,bool *isProgramRunnig);
void maker_input(MapMaker *pMapMaker,SDL_Event event,bool *isGameRunnig,bool *isProgramRunnig);

void maker_update(MapMaker *pMapMaker);
void maker_render(SDL_Renderer *pRendererer,MapMaker *pMapMaker,Map *pMap);

void saveMademap(MapMaker *pMapMaker);


#endif

// det kommer att var en selekt funktion där man sedan plaserar ut de 
// tiles man vill och därefter väljer en till 