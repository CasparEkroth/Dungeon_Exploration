#ifndef PLAYER_H
#define PLAYER_H
#include "map.h"


#define NR_OF_SPRITS 20
#define NR_OF_ITEMS 10
#define NAME 40
#define PLAYER_HEIGHT 64
#define PLAYER_WIDTH 32
#define ITEM_SIZE 32


typedef struct {
    int idNummber; //kommer begöva komma på en struktur för id
    SDL_Rect itemRect;
}Items;

typedef struct {
    bool open;
    int nummberOfItems;
    Items *pItems[NR_OF_ITEMS]; 
}Inventory;

typedef struct{
    char playerName[NAME];
    int totolExp, level;
    Inventory *pInvetory;
    SDL_Rect rect;
    SDL_Rect sprits[NR_OF_SPRITS];
    int indexOfSprits;
    SDL_Texture *pSprit_shet; // nedd to finde 
}Player;

Player* CreatePlayer(SDL_Renderer *pRederere,char playerName[NAME], int window_h, int window_w);

void lodePlayer(Player *pPlayer,char playerName[NAME]);
void getPlayerName(char playerName[NAME]);


#endif