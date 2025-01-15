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

#define NUMMBER_OF_TILSE_Y 25
#define NUMMBER_OF_TILSE_X 25
#define NUMMBER_OF_DIFFERENT_TILSE 5 

typedef struct {
    char tileMap[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X];
    SDL_Texture *pTileShet;
    SDL_Rect tileIndex[NUMMBER_OF_DIFFERENT_TILSE];
}Map;

typedef struct {
    TTF_Font *font;

}Menu;

void redeFileForMap(char tileMap[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X],char fileName[],char newRom[]);
void printMap(char tileMap[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X]);

#endif 