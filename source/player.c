#include "player.h"

Player* CreatePlayer(SDL_Renderer *pRederere,char playerName[NAME], int window_h, int window_w){
    Player *pPlayer = malloc(sizeof(Player));
    lodePlayer(pPlayer,playerName);
    pPlayer->rect.h = PLAYER_HEIGHT;
    pPlayer->rect.w = PLAYER_WIDTH;
    pPlayer->rect.x = window_w/2;
    pPlayer->rect.y = window_h/2;
    pPlayer->indexOfSprits = 0;
    SDL_Surface *tmpPlayer = IMG_Load("!"); // hitta en fil som funkar 
    if(!tmpPlayer){
        fprintf(stderr,"Error loding surface for player shet, %s\n",IMG_GetError());
        return NULL;
    }
    pPlayer->pSprit_shet = SDL_CreateTextureFromSurface(pRederere,tmpPlayer);
    SDL_FreeSurface(tmpPlayer);
    if(!pPlayer->pSprit_shet){
        fprintf(stderr,"Error creating textrur for player, %s\n",IMG_GetError());
        return NULL;
    }
    pPlayer->sprits[0] = (SDL_Rect){0,0,0,0}; //ex

    return pPlayer;
}

void lodePlayer(Player *pPlayer,char playerName[NAME]){
    //läs in från fil
    //vi vill läsa in (exp, level,och inventory)
    char buffer[256];
    FILE *fp = fopen("resourses/savdeCaracter.txt","r");
    if(fp == NULL){
        fprintf(stderr,"Error: Clude not open savdeCaracter.txt \n");
        return;
    }
    while (fgets(buffer, sizeof(buffer), fp)){
        //trimWhitespace(buffer); 
        if (strcmp(buffer, playerName) == 0) {
            fscanf(fp," %d\n",&pPlayer->totolExp);
            fscanf(fp," %d\n",&pPlayer->pInvetory->nummberOfItems);
            for (int i = 0; i < pPlayer->pInvetory->nummberOfItems; i++){
                fscanf(fp," %d\n",&pPlayer->pInvetory->pItems[i]->idNummber);
                pPlayer->pInvetory->pItems[i]->itemRect.w = ITEM_SIZE;
                pPlayer->pInvetory->pItems[i]->itemRect.h = ITEM_SIZE;
            }
            
            break;
        }
    }
    fclose(fp);
}

void getPlayerName(char playerName[NAME]){
    //kskriver till terminalen eller fixar ett intefase där man kan skriva 
}