#include "map.h"

void printMap(char tileMap[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X]){
    for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++){
        for (int x = 0; x < NUMMBER_OF_TILSE_X; x++){
            printf("%c",tileMap[y][x]);
            //printf("%d",tileMap);
        }
        printf("\n");
    }
}

void renderTile(SDL_Renderer *pRenderer,char tile,SDL_Rect tileIndex[NUMMBER_OF_DIFFERENT_TILSE],
                SDL_Rect tileRect,SDL_Texture *pTileShet){
    switch (tile){
    case 'a': //void
        SDL_RenderCopy(pRenderer,pTileShet,&tileIndex[0],&tileRect);
        break;
    case 'b': 
        SDL_RenderCopy(pRenderer,pTileShet,&tileIndex[1],&tileRect);
        break;
    case 'c':
        SDL_RenderCopy(pRenderer,pTileShet,&tileIndex[2],&tileRect);
        break;
    case 'd':
        SDL_RenderCopy(pRenderer,pTileShet,&tileIndex[3],&tileRect);//wall
        break;
    case 'e':
        //SDL_RenderCopy(pRenderer,pTileShet,&tileIndex[3],&tileRect);//wall
        SDL_RenderCopy(pRenderer,pTileShet,&tileIndex[4],&tileRect);//
        break;
    case 'f':
        //SDL_RenderCopy(pRenderer,pTileShet,&tileIndex[1],&tileRect);
        SDL_RenderCopy(pRenderer,pTileShet,&tileIndex[5],&tileRect);
        break;
    case 'g':
        SDL_RenderCopy(pRenderer,pTileShet,&tileIndex[6],&tileRect);//
        break;
    case 'h':
        //SDL_RenderCopy(pRenderer,pTileShet,&tileIndex[1],&tileRect);
        //SDL_RendererFlip a;
        SDL_RenderCopy(pRenderer,pTileShet,&tileIndex[7],&tileRect);
        break;
    case 'i':
        SDL_RenderCopy(pRenderer,pTileShet,&tileIndex[2],&tileRect);
        SDL_RenderCopy(pRenderer,pTileShet,&tileIndex[8],&tileRect);
        break;
    case 'j':
        SDL_RenderCopy(pRenderer,pTileShet,&tileIndex[2],&tileRect);
        SDL_RenderCopy(pRenderer,pTileShet,&tileIndex[9],&tileRect);
        break;
    case 'k':
        SDL_RenderCopy(pRenderer,pTileShet,&tileIndex[10],&tileRect);
        break;
    case 'l':
        SDL_RenderCopy(pRenderer,pTileShet,&tileIndex[11],&tileRect);
        break;
    case 'm':
        SDL_RenderCopy(pRenderer,pTileShet,&tileIndex[12],&tileRect);
        break;
    case 'n':
        SDL_RenderCopy(pRenderer,pTileShet,&tileIndex[2],&tileRect);
        SDL_RenderCopy(pRenderer,pTileShet,&tileIndex[13],&tileRect);
        break;
    case 'o':
        SDL_RenderCopy(pRenderer,pTileShet,&tileIndex[2],&tileRect);
        SDL_RenderCopy(pRenderer,pTileShet,&tileIndex[14],&tileRect);
        break;
    case 'p':
        SDL_RenderCopy(pRenderer,pTileShet,&tileIndex[15],&tileRect);
        break;
    case 'q':
        SDL_RenderCopy(pRenderer,pTileShet,&tileIndex[16],&tileRect);
        break;
    case 'r':
        SDL_RenderCopy(pRenderer,pTileShet,&tileIndex[2],&tileRect);
        SDL_RenderCopy(pRenderer,pTileShet,&tileIndex[17],&tileRect);
        break;
        //corner dowen
    default:
        break;
    }
}


void renderMap(SDL_Renderer *pRenderer,char tileMap[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X],
                SDL_Rect tileIndex[NUMMBER_OF_DIFFERENT_TILSE],SDL_Texture *pTileShet,
                SDL_Rect tileRect[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X]){
    for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++){
        for (int  x = 0; x < NUMMBER_OF_TILSE_X; x++){
        renderTile(pRenderer,tileMap[y][x],tileIndex,tileRect[y][x],pTileShet);
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
                trimWhitespace(tileMap[y]);
            }
            break;
        }
    }
    fclose(fp);
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
    pMap->tileIndex[3] = (SDL_Rect){101,16,16,16}; //wall 1 (flat)
    pMap->tileIndex[4] = (SDL_Rect){144,165,16,16}; //wall/turn (left -> dowen)
    pMap->tileIndex[5] = (SDL_Rect){352,256,16,16}; //wall side (left)
    pMap->tileIndex[6] = (SDL_Rect){128,165,16,16}; //wall/turn (rhigt -> dowen)
    pMap->tileIndex[7] = (SDL_Rect){656,256,16,16}; //wall side (left)(neds Ex)
    pMap->tileIndex[8] = (SDL_Rect){0,112,16,16};//skull
    pMap->tileIndex[9] = (SDL_Rect){16,112,16,16};//chest
    pMap->tileIndex[10] = (SDL_Rect){160,80,16,16};//piler part 1
    pMap->tileIndex[11] = (SDL_Rect){160,96,16,16};//piler part 2
    pMap->tileIndex[12] = (SDL_Rect){160,114,16,16};//piler part 3
    pMap->tileIndex[13] = (SDL_Rect){143,208,16,16};//lever 1
    pMap->tileIndex[14] = (SDL_Rect){159,208,16,16};//lever 2
    pMap->tileIndex[15] = (SDL_Rect){192,79,16,16};// stari downe
    pMap->tileIndex[16] = (SDL_Rect){80,0,16,16};//top wall
    pMap->tileIndex[17] = (SDL_Rect){0,0,16,16};//lever 2

    return pMap;
}

void updatCurentMap(SDL_Rect tileRect[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X],int TILE_SIZE_W,int TILE_SIZE_H){
    for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++){
        for (int x = 0; x < NUMMBER_OF_TILSE_X; x++){
            tileRect[y][x].w = TILE_SIZE_W;
            tileRect[y][x].h = TILE_SIZE_H;     
            tileRect[y][x].x = (x * TILE_SIZE_W);
            tileRect[y][x].y = (y * TILE_SIZE_H);
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

Camera *initialize_camera(void){
    Camera* pCamera = malloc(sizeof(Camera));
        if(!pCamera){
        fprintf(stderr,"Memory allocation failed for Camera\n");
        return NULL;
    }
    pCamera->Ofset.x = 0;
    pCamera->Ofset.y = 0;
    pCamera->curentPos.x = STARTING_WINDOW_WIDTH/2;
    pCamera->curentPos.y = STARTING_WINDOW_HEIGHT/2;
    return pCamera;
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

