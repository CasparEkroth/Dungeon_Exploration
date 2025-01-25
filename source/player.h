#ifndef PLAYER_H
#define PLAYER_H
#include <SDL.h>
#include <stdbool.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <stdlib.h> 
#include <stdio.h>

#define NR_OF_SPRITS 20

typedef struct {
    // får komma på ett bra sett att strukturera detta 
}Inventory;



typedef struct{
    //Inventory *pInvetory;
    SDL_Rect rect;
    SDL_Rect sprits[NR_OF_SPRITS];
    int indexOfSprits;
    SDL_Texture *pSprit_shet; // nedd to finde 
    
}Player;



#endif