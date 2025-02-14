#include "map.h"

void printMap(char tileMap[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X]){
    for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++){
        for (int x = 0; x < NUMMBER_OF_TILSE_X; x++){
            printf("%c",tileMap[y][x]);
            //printf("%d",tileMap[y][x]);
        }
        printf("\n");
}
}

void renderMap(SDL_Renderer *pRenderer, Map *pMap){
    for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++){
        for (int  x = 0; x < NUMMBER_OF_TILSE_X; x++){
            switch (pMap->tileMap[y][x]){
            case 'v': //void
                SDL_RenderCopy(pRenderer,pMap->pTileShet,&pMap->tileIndex[2],&pMap->tileRect[y][x]);
                break;
            case 'k': 
                SDL_RenderCopy(pRenderer,pMap->pTileShet,&pMap->tileIndex[3],&pMap->tileRect[y][x]);
                break;
            case 'e':
                SDL_RenderCopy(pRenderer,pMap->pTileShet,&pMap->tileIndex[4],&pMap->tileRect[y][x]);
                break;
            case 'a':
                SDL_RenderCopy(pRenderer,pMap->pTileShet,&pMap->tileIndex[1],&pMap->tileRect[y][x]);
                SDL_RenderCopy(pRenderer,pMap->pTileShet,&pMap->tileIndex[5],&pMap->tileRect[y][x]);
                break;
            case 'b':
                SDL_RenderCopy(pRenderer,pMap->pTileShet,&pMap->tileIndex[6],&pMap->tileRect[y][x]);
                break;
            case 'c':
                SDL_RenderCopy(pRenderer,pMap->pTileShet,&pMap->tileIndex[1],&pMap->tileRect[y][x]);
                SDL_RendererFlip a;
                SDL_RenderCopyEx(pRenderer,pMap->pTileShet,&pMap->tileIndex[7],&pMap->tileRect[y][x],180,NULL,a);
                break;
            default:
                break;
            }
        }
        
    }
}

void trimWhitespace(char *str) {// Ta bort extra whitespace
    char *end;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = 0;
}

void redeFileForMap(char tileMap[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X], char fileName[], char newRom[]){
    char buffer[256];
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) {
        fprintf(stderr,"Error: Clude not open %s!\n",fileName);
        return;
    }
    while (fgets(buffer, sizeof(buffer), fp)) {
        trimWhitespace(buffer); 
        if (strcmp(buffer, newRom) == 0) {
            for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++) {
                for (int x = 0; x < NUMMBER_OF_TILSE_X; x++) {
                    fscanf(fp, " %c", &tileMap[y][x]);
                }
            }
            break;
        }
    }
    fclose(fp);
    //printMap(tileMap);
}

Map *createMap(SDL_Renderer *pRenderre){
    Map *pMap = malloc(sizeof(Map));
    strcpy(pMap->tileRulseFile,"resourses/tileRules.txt");
    strcpy(pMap->curentRoom,"start");
    stpcpy(pMap->mapFile,"resourses/mapFile.txt");

    pMap->TILE_SIZE_H = TILE_SIZE;
    pMap->TILE_SIZE_W = TILE_SIZE;

    for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++){
        for (int x = 0; x < NUMMBER_OF_TILSE_X; x++){
            pMap->tileRect[y][x].w = pMap->TILE_SIZE_W;
            pMap->tileRect[y][x].h = pMap->TILE_SIZE_H;     
            pMap->tileRect[y][x].x = (x * pMap->TILE_SIZE_W);
            pMap->tileRect[y][x].y = (y * pMap->TILE_SIZE_H);
        }
    }
    redeFileForMap(pMap->tileMap,pMap->mapFile,pMap->curentRoom);
    SDL_Surface *tmpMap = IMG_Load("resourses/map.png");
    if(!tmpMap){
        fprintf(stderr,"Error creating Surface for map, %s\n",IMG_GetError());
        return NULL;
    }
    pMap->pTileShet = SDL_CreateTextureFromSurface(pRenderre,tmpMap);
    SDL_FreeSurface(tmpMap);
    if(!pMap->pTileShet){
        fprintf(stderr,"Error creating Texture for map, %s\n",IMG_GetError());
        return NULL;
    }
    pMap->tileIndex[0] = (SDL_Rect){80,80,16,16}; // floor 1
    pMap->tileIndex[1] = (SDL_Rect){80,96,16,16}; // floor 2
    pMap->tileIndex[2] = (SDL_Rect){80,64,16,16}; // floor 3
    pMap->tileIndex[3] = (SDL_Rect){101,13,16,16}; //wall 1 (flat)
    pMap->tileIndex[4] = (SDL_Rect){144,165,16,16}; //wall/turn (left -> dowen)
    pMap->tileIndex[5] = (SDL_Rect){80,150,16,16}; //wall side (left)
    pMap->tileIndex[6] = (SDL_Rect){127,165,16,16}; //wall/turn (rhigt -> dowen)
    pMap->tileIndex[7] = (SDL_Rect){81,150,16,16}; //wall side (left)(neds Ex)
    return pMap;
}

void updatCurentMap(Map *pMap){
    for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++){
        for (int x = 0; x < NUMMBER_OF_TILSE_X; x++){
            pMap->tileRect[y][x].w = pMap->TILE_SIZE_W;
            pMap->tileRect[y][x].h = pMap->TILE_SIZE_H;     
            pMap->tileRect[y][x].x = (x * pMap->TILE_SIZE_W);
            pMap->tileRect[y][x].y = (y * pMap->TILE_SIZE_H);
        }
    }
}

ScreenAndInput* initialize_input(void){
    ScreenAndInput* pScreenAndInput = malloc(sizeof(ScreenAndInput));
        if(!pScreenAndInput){
        fprintf(stderr,"Memory allocation failed for ScreenAndInput\n");
        return NULL;
    }
    pScreenAndInput->currentTime = 0;
    pScreenAndInput->previousTime = 0;
    pScreenAndInput->deltaTimeResize = 0;
    return pScreenAndInput;
}

bool colitino(SDL_Rect A,SDL_Rect B){
    if(A.x + A.w >= B.x && 
        A.x <= B.x + B.w &&
        A.y + A.h >= B.y &&
        A.y <= B.y + B.h){
        return true;
    }else{
        return false;
    }
}

bool pointInRect(SDL_Rect A, SDL_Point P) {
    if (P.x >= A.x && 
        P.x <  A.x + A.w && 
        P.y >= A.y && 
        P.y <  A.y + A.h){
        return true;
    }
    return false;
}

