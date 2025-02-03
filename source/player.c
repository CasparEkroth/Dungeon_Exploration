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
    pPlayer->deltaTime = 0;
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
    // kommer behöva en inverterad bil för att få player att kunna vända 
    // sig åt vänster 
    pPlayer->sprits[0] = (SDL_Rect){300,160,32,64}; //idel fornt 
    pPlayer->sprits[1] = (SDL_Rect){170,280,32,64}; // gå fram 1
    pPlayer->sprits[2] = (SDL_Rect){170,530,32,64}; //gå fram 2
    pPlayer->sprits[3] = (SDL_Rect){170,780,32,64}; //gå fram 3
    pPlayer->sprits[4] = (SDL_Rect){170,1020,32,64}; //gå fram 4
    pPlayer->sprits[5] = (SDL_Rect){170,1270,32,64}; //gå fram 5

    pPlayer->sprits[6] = (SDL_Rect){430,160,32,64}; //idel back
    pPlayer->sprits[7] = (SDL_Rect){300,280,32,64}; //gå back 1
    pPlayer->sprits[8] = (SDL_Rect){300,530,32,64}; //gå back 2
    pPlayer->sprits[9] = (SDL_Rect){300,780,32,64}; //gå back 3
    pPlayer->sprits[10] = (SDL_Rect){300,1020,32,64}; //gå back 4
    pPlayer->sprits[11] = (SDL_Rect){300,1270,32,64}; //gå back 5

    pPlayer->sprits[12] = (SDL_Rect){170,160,32,64}; //idel rhigt
    pPlayer->sprits[13] = (SDL_Rect){45,280,32,64}; // gå rhigt 1
    pPlayer->sprits[14] = (SDL_Rect){45,530,32,64}; //gå rhigt 2
    pPlayer->sprits[15] = (SDL_Rect){45,780,32,64}; //gå rhigt 3
    pPlayer->sprits[16] = (SDL_Rect){45,1020,32,64}; //gå rhigt 4
    pPlayer->sprits[17] = (SDL_Rect){45,1270,32,64}; //gå rhigt 5

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
    int delay = 100;
    if(pPlayer->deltaTime>= delay){
        if(Ofset.y<0){ // upp
            pPlayer->indexOfSprits++;
            if(pPlayer->indexOfSprits>=6){
                pPlayer->indexOfSprits = 1; 
            }
        }else if (Ofset.y>0){ // down
            pPlayer->indexOfSprits++;
            if(pPlayer->indexOfSprits>=12){
                pPlayer->indexOfSprits = 7; 
            }
        }
        if(Ofset.x<0){ //rhigt 
            pPlayer->indexOfSprits++;
            if(pPlayer->indexOfSprits>=18){
                pPlayer->indexOfSprits = 13; 
            }
        }else if(Ofset.x>0){ //left (is coming)
            pPlayer->indexOfSprits++;
            if(pPlayer->indexOfSprits>=6){
                pPlayer->indexOfSprits = 1; 
            }
        }
        pPlayer->deltaTime = 0;
    }
    SDL_RenderCopy(pRenderer,pPlayer->pSprit_shet,&pPlayer->sprits[pPlayer->indexOfSprits],&pPlayer->rect);
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

void updatePlayerSize(Player *pPlayer, Map *pMap, SDL_Point curentPos){
    pPlayer->rect.h = (2* pMap->TILE_SIZE_H);
    pPlayer->rect.w = (pMap->TILE_SIZE_W);
    pPlayer->rect.x = curentPos.x;
    pPlayer->rect.y = curentPos.y;
}