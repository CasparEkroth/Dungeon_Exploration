#ifndef MAP_H
#define MAP_H
#include <SDL.h>
#include <stdbool.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

#define FILE_LENGTH 40
#define NUMMBER_OF_TILSE_Y 25
#define NUMMBER_OF_TILSE_X 25
#define NUMMBER_OF_DIFFERENT_TILSE 10 
#define TILE_SIZE 32 

#define VISIBLE_WINDOW_Y 15 // * tile_size (v)
#define VISIBLE_WINDOW_X 20


typedef struct {
    int TILE_SIZE_W,TILE_SIZE_H;
    char tileMap[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X];
    SDL_Texture *pTileShet;
    SDL_Rect tileIndex[NUMMBER_OF_DIFFERENT_TILSE];//sprits
    SDL_Rect tileRect[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X];//pos
    char curentRoom[FILE_LENGTH];
    char mapFile[FILE_LENGTH];
    char tileRulseFile[FILE_LENGTH];
}Map;

typedef struct {
    Uint32 currentTime;
    Uint32 previousTime;
    bool keys[SDL_NUM_SCANCODES];
    int deltaTimeResize;
}ScreenAndInput;

Map *createMap(SDL_Renderer *pRenderre);
void renderMap(SDL_Renderer *pRenderer, Map *pMap);
void updatCurentMap(Map *pMap);

void trimWhitespace(char *str);
void redeFileForMap(char tileMap[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X],char fileName[],char newRom[]);
void printMap(char tileMap[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X]);

ScreenAndInput* initialize_input(void);

bool colitino(SDL_Rect A,SDL_Rect B);


#endif 