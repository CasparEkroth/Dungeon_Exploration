//kart in läsning kommmer att ske via filer 
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
#define NUMMBER_OF_DIFFERENT_TILSE 5 
#define TILE_SIZE 32 

typedef struct {
    char tileMap[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X];
    SDL_Texture *pTileShet;
    SDL_Rect tileIndex[NUMMBER_OF_DIFFERENT_TILSE];//sprits
    SDL_Rect tileRect[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X];//pos
    char curentRoom[FILE_LENGTH];
    char mapFile[FILE_LENGTH];
    char tileRulseFile[FILE_LENGTH];
}Map;

typedef struct {
    TTF_Font *font;

}Menu;

Map *createMap(SDL_Renderer *pRenderre);


void redeFileForMap(char tileMap[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X],char fileName[],char newRom[]);
void printMap(char tileMap[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X]);

#endif 