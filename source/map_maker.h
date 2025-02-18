#ifndef MAP_MAKER_H
#define MAP_MAKER_H
#include "game.h"

#define NR_OF_ROMS 3
#define SPEED (32)

typedef struct {
    char selectedTile;
    int fileIdex;
    SDL_Point highlight_rect;
    SDL_Point mapOfset,mousePos;
    char fileName[NAME];
    char romeName[NAME];
    bool isNewRoom;
    char map[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X];
    SDL_Rect rect_map[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X];
    bool isSavede,isChosingNewTile,isMakingMap;
    bool keys[SDL_NUM_SCANCODES];
}MapMaker;

MapMaker* initMapMaker(char fileName[NAME],int tileSizeW,int tileSizeH,char romeName[NAME],char fileList[NAME]);

bool isOnListofRom(char fileName[NAME],char romName[NAME],int *fileIndex);


void maker(MapMaker *pMapMaker, Game *pGame,bool *isGameRunnig,bool *isProgramRunnig);
void maker_input(MapMaker *pMapMaker,SDL_Event event,bool *isGameRunnig,bool *isProgramRunnig);

void maker_update(MapMaker *pMapMaker);
void maker_render(SDL_Renderer *pRendererer,MapMaker *pMapMaker,Map *pMap,SDL_Event event);

void saveMademap(MapMaker *pMapMaker);


#endif

// det kommer att var en selekt funktion där man sedan plaserar ut de 
// tiles man vill och därefter väljer en till 