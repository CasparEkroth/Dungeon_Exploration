#include "map_maker.h"
//input 
//render 
//seving to file                                                                                //ta bort
MapMaker* initMapMaker(char fileName[NAME],int tileSizeW,int tileSizeH,char romeName[NAME],char fileList[NAME]){
    MapMaker* pMapMaker = malloc(sizeof(MapMaker));
    if(!pMapMaker){
        fprintf(stderr,"Erorr alocating memory for MapMaker\n");
        return NULL;
    }
    if(isOnListofRom(fileName,romeName,&pMapMaker->fileIdex)){
        pMapMaker->isNewRoom = false;
        redeFileForMap(pMapMaker->map,fileName,romeName);
    }else{
        pMapMaker->isNewRoom = true;
        for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++){
            for (int x = 0; x < NUMMBER_OF_TILSE_X; x++){
                pMapMaker->map[y][x] = ('a'-1);
            }
        }
    }
    pMapMaker->isChosingNewTile = false;
    pMapMaker->isMakingMap = true;
    pMapMaker->isSavede = false;
    strcpy(pMapMaker->fileName,fileName);
    strcpy(pMapMaker->romeName,romeName);
    for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++){
        for (int x = 0; x < NUMMBER_OF_TILSE_X; x++){
            pMapMaker->rect_map[y][x].w = tileSizeW;
            pMapMaker->rect_map[y][x].h = tileSizeH;
            pMapMaker->rect_map[y][x].y = (tileSizeH*y);
            pMapMaker->rect_map[y][x].x = (tileSizeW*x);
        }
    }
    pMapMaker->selectedTile = ' ';
    pMapMaker->highlight_rect = (SDL_Point){0,0};
    pMapMaker->mapOfset = (SDL_Point){0,0};
    pMapMaker->mousePos = (SDL_Point){0,0};
    return pMapMaker;
} 

void maker(MapMaker *pMapMaker, Game *pGame,bool *isGameRunnig,bool *isProgramRunnig){
    SDL_Event event;
    while (pMapMaker->isMakingMap){
        //if(!pMapMaker->isMakingMap) return;
        //printf("in maker\n");
        while (SDL_PollEvent(&event)){
            maker_input(pMapMaker,event,isGameRunnig,isProgramRunnig);
        }
        maker_update(pMapMaker);
        maker_render(pGame->pRenderer,pMapMaker,pGame->pMap,event);
    }
    saveMademap(pMapMaker);
    free(pMapMaker);
}

void maker_render(SDL_Renderer *pRenderer,MapMaker *pMapMaker,Map *pMap,SDL_Event event){
    SDL_RenderClear(pRenderer);
    Uint32 mouseState = SDL_GetMouseState(&pMapMaker->mousePos.x,&pMapMaker->mousePos.y);
    if(pMapMaker->isChosingNewTile){
        SDL_Rect A ={32,32,32,32};
        for (int i = 0; i <NUMMBER_OF_DIFFERENT_TILSE; i++){
            SDL_RenderCopy(pRenderer,pMap->pTileShet,&pMap->tileIndex[i],&A);
            if(pointInRect(A,pMapMaker->mousePos)){
                SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);  // Red
                SDL_RenderDrawRect(pRenderer, &A); 
                if(mouseState){
                    pMapMaker->selectedTile = ('a'+i);
                    //printf("%c\n",pMapMaker->selectedTile);
                    pMapMaker->isChosingNewTile = false;
                }
            }
            A.x += 64;
        }
    }else{
        renderMap(pRenderer,pMapMaker->map,pMap->tileIndex,pMap->pTileShet,pMapMaker->rect_map);
        SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);  // Red
        if (pMapMaker->highlight_rect.x < NUMMBER_OF_TILSE_X && pMapMaker->highlight_rect.y < NUMMBER_OF_TILSE_Y) {
            SDL_RenderDrawRect(pRenderer, &pMapMaker->rect_map[pMapMaker->highlight_rect.y][pMapMaker->highlight_rect.x]);
        }
    }
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    SDL_RenderPresent(pRenderer);
}

void maker_update(MapMaker *pMapMaker){
    for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++){
        for (int x = 0; x < NUMMBER_OF_TILSE_X; x++){
            pMapMaker->rect_map[y][x].x += pMapMaker->mapOfset.x;
            pMapMaker->rect_map[y][x].y += pMapMaker->mapOfset.y;
        }
    }
    pMapMaker->mapOfset =(SDL_Point){0,0};
}

void maker_input(MapMaker *pMapMaker,SDL_Event event,bool *isGameRunnig,bool *isProgramRunnig){
    SDL_ShowCursor(SDL_ENABLE);
    SDL_Point mouse;
    Uint32 mouseState = SDL_GetMouseState(&mouse.x, &mouse.y);
    pMapMaker->mousePos = mouse;
    switch (event.type){
    case SDL_QUIT:
        pMapMaker->isMakingMap = false;
        isGameRunnig = false;
        isProgramRunnig = false;
        break;
    case SDL_MOUSEBUTTONDOWN:
        pMapMaker->keys[event.button.state] = SDL_PRESSED;
        break;// fixa plasering va vld tile samt att man (input) för att göra en tile till (void)
    case SDL_MOUSEBUTTONUP:
        pMapMaker->keys[event.button.state] = SDL_RELEASED;
        break;
    case SDL_KEYDOWN:
        pMapMaker->keys[event.key.keysym.scancode] = true;
        break;
    case SDL_KEYUP:
        pMapMaker->keys[event.key.keysym.scancode] = false;
        break;
    default:
        break;
    }
    for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++){
        for (int x = 0; x < NUMMBER_OF_TILSE_X; x++){
            if(pointInRect(pMapMaker->rect_map[y][x],mouse)){
                pMapMaker->highlight_rect.x = x;
                pMapMaker->highlight_rect.y = y;
                break;
            }
        }
    }
    if(mouseState)pMapMaker->map[pMapMaker->highlight_rect.y][pMapMaker->highlight_rect.x] = pMapMaker->selectedTile;
    if(pMapMaker->keys[SDL_SCANCODE_ESCAPE]){
        pMapMaker->isMakingMap = false;
        isGameRunnig = false;
        isProgramRunnig = false;
    }
    if(pMapMaker->keys[SDL_SCANCODE_UP]) pMapMaker->mapOfset.y = SPEED;
    if(pMapMaker->keys[SDL_SCANCODE_DOWN]) pMapMaker->mapOfset.y -= SPEED;
    if(pMapMaker->keys[SDL_SCANCODE_LEFT]) pMapMaker->mapOfset.x = SPEED;
    if(pMapMaker->keys[SDL_SCANCODE_RIGHT]) pMapMaker->mapOfset.x -= SPEED;
    if(pMapMaker->keys[SDL_SCANCODE_N]) pMapMaker->isChosingNewTile = true;
    if(pMapMaker->keys[SDL_SCANCODE_RETURN]) pMapMaker->isChosingNewTile = false;
}

void saveMademap(MapMaker *pMapMaker){
    FILE *fp = fopen(pMapMaker->fileName, "r");
    if (!fp) {
        fprintf(stderr, "Error: Could not open %s for reading!\n", pMapMaker->fileName);
        return;
    }
    FILE *tmp = fopen("tmp.txt", "w");
    if (!tmp) {
        fprintf(stderr, "Error: Could not open tmp.txt for writing!\n");
        fclose(fp);
        return;
    }
    char buffer[256];
    int count = 0;
    int skipCondition = pMapMaker->fileIdex;
    while (fgets(buffer, sizeof(buffer), fp) != NULL){
        if(count == skipCondition){
            for (int i = 0; i < NUMMBER_OF_TILSE_Y; i++){
                fgets(buffer, sizeof(buffer), fp);
            }
            break;
        }
        trimWhitespace(buffer);
        fprintf(tmp,"%s\n",buffer);
        count++;
    }
    fprintf(tmp,"%s\n",pMapMaker->romeName);
    for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++){
        for (int x = 0; x < NUMMBER_OF_TILSE_X; x++){
            fprintf(tmp,"%c",pMapMaker->map[y][x]);
        }
        fprintf(tmp,"\n");
    }
    while (fgets(buffer,sizeof(buffer),fp) != NULL){
        trimWhitespace(buffer);
        fprintf(tmp,"%s\n",buffer);
    }
    
    fclose(fp);
    fclose(tmp);

    remove(pMapMaker->fileName);
    rename("tmp.txt", pMapMaker->fileName);
}

bool isOnListofRom(char fileName[NAME],char romName[NAME],int *fileIndex){
    char buffer[256];
    int contRom = 0,line = 0;

    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) {
        fprintf(stderr,"Error: Clude not open %s!\n",fileName);
        return NULL;
    }
    while (fgets(buffer, sizeof(buffer), fp) != NULL){
        trimWhitespace(buffer);
        if(strcmp(buffer,romName) == 0){
            fclose(fp);
            *fileIndex = line;
            printf("%d line ",*fileIndex);
            return true;
        }
        line++;
    }
    fclose(fp);
    return false;
}
