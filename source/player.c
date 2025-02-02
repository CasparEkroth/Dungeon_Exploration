#include "player.h"

Player* createPlayer(SDL_Renderer *pRederere,char playerName[NAME], int window_h, int window_w){
    Player *pPlayer = malloc(sizeof(Player));
    if (!pPlayer) {
        fprintf(stderr, "Memory allocation failed for Player\n");
        return NULL;
    }
    pPlayer->pInventory = malloc(sizeof(Inventory));
    if (!pPlayer->pInventory) {
        fprintf(stderr, "Memory allocation failed for Inventory\n");
        free(pPlayer);
        return NULL;
    }
    for (int i = 0; i < MAX_ITEMS; i++){
        pPlayer->pInventory->pItems[i] = malloc(sizeof(Item));
        if (!pPlayer->pInventory->pItems[i]) {
            fprintf(stderr, "Memory allocation failed for Items\n");
            free(pPlayer->pInventory);
            free(pPlayer);
            return NULL;
        }
    }
    strcpy(pPlayer->playerName,playerName);
    lodePlayer(pPlayer,playerName);
    pPlayer->rect.h = PLAYER_HEIGHT;
    pPlayer->rect.w = PLAYER_WIDTH;
    pPlayer->rect.x = window_w/2;
    pPlayer->rect.y = window_h/2;
    pPlayer->indexOfSprits = 0;
    pPlayer->pInventory->open = false;
    SDL_Surface *tmpPlayer = IMG_Load("resourses/Player_shet.png"); // hitta en fil som funkar 
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
        trimWhitespace(buffer);                       
        if (strcmp(buffer, playerName) == 0) {
            fscanf(fp," %d\n",&pPlayer->totolExp);
            fscanf(fp," %d\n",&pPlayer->pInventory->nummberOfItems);
            for (int i = 0; i < pPlayer->pInventory->nummberOfItems; i++){
                fscanf(fp," %d\n",&pPlayer->pInventory->pItems[i]->idNummber);
                pPlayer->pInventory->pItems[i]->itemRect.w = ITEM_SIZE;
                pPlayer->pInventory->pItems[i]->itemRect.h = ITEM_SIZE;
            }
            
            break;
        }
    }
    fclose(fp);
}


void rednerPlayer(SDL_Renderer *pRenderer, Player *pPlayer, SDL_Point Ofset){
    //gör begränsningar genomm delta time 
}



void getPlayerName(char playerName[NAME]){ //kommer senare 
    //kskriver till terminalen eller fixar ett intefase där man kan skriva 
    // detta kommer vi göra i menyn 
}

void showInventory(Player *pPlayer){ // inte prio
    //fix ett sätt att komma åt 
    //samt att se föredragds vid 
    //esc == för att ta ner invetory
    //mussstyrt hantering 
}

void printPlayer(Player *pPlayer){
    printf("%s\ntotal Exp %d\nNr of intems %d\n",
    pPlayer->playerName,
    pPlayer->totolExp,
    pPlayer->pInventory->nummberOfItems);
    for (int i = 0; i < pPlayer->pInventory->nummberOfItems; i++){
        printf("item %d = id: %d\n",i,pPlayer->pInventory->pItems[i]->idNummber);
    }
}