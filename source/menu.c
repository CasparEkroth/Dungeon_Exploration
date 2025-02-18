#include "menu.h"

Boolien* initialize_Boolien(void){
    Boolien* pBoolien = malloc(sizeof(Boolien));
    if(!pBoolien){
        fprintf(stderr,"Memory allocation failed for Boolien(menu)\n");
        return NULL;
    }
    pBoolien->isOpen = true;
    pBoolien->isChoosingCharacter = false;
    pBoolien->isDone = false;
    pBoolien->isWriting = false;
    pBoolien->isChoosingCharacter = false;
    pBoolien->isMakingMap = false;
    return pBoolien;
}

Menu* initialize_Menu(SDL_Renderer *pRenderer,SDL_Window *pWindow){
    Menu* pMenu = malloc(sizeof(Menu));
    if(!pMenu){
        fprintf(stderr,"Memory allocation failed for Menu\n");
        return NULL;
    }
    pMenu->leter = 0;
    pMenu->highlight_rect = 0;
    char empty = {0};
    strcpy(pMenu->stringPlayerName,&empty);

    pMenu->rect[1] = (SDL_Rect){50,50,15,50}; //koll vart de ska vara 
    pMenu->MenuPlasment[0] =(SDL_Point){11,3};
    pMenu->pFont = TTF_OpenFont("resourses/RubikMaps-Regular.ttf",24);
        if(!pMenu->pFont){
        fprintf(stderr,"Error: Loding font: %s\n", TTF_GetError());
        return false;
    }
    pMenu->playerName = makeStringInToSDL_Texture("",pMenu->pFont,pRenderer);
    SDL_Surface *pBack = IMG_Load("resourses/background.jpg");
    if(!pBack){
        fprintf(stderr,"Error creating suface for backgrund(menu): %s",IMG_GetError());
        return NULL;
    }
    pMenu->pBackTextur = SDL_CreateTextureFromSurface(pRenderer,pBack);
    SDL_FreeSurface(pBack);
    if(!pMenu->pBackTextur){
        fprintf(stderr,"Error creating textur for backgrung(menu): %s",SDL_GetError());
        return NULL;
    }
    int width, height;
    SDL_GetWindowSize(pWindow, &width, &height);
    pMenu->rect[0] =(SDL_Rect){0,0,width,height};

    pMenu->pMenuOptions[0] = makeStringInToSDL_Texture("PLAY",pMenu->pFont,pRenderer);
    pMenu->MenuPlasment[1] =(SDL_Point){1,11};//x,y
    pMenu->rect[2] = setingSizeOfStringToRect("PLAY",pMenu->MenuPlasment[1],TILE_SIZE,TILE_SIZE);
    pMenu->pMenuOptions[1] = makeStringInToSDL_Texture("BACK",pMenu->pFont,pRenderer);
    pMenu->MenuPlasment[2] = (SDL_Point){1,12};
    pMenu->rect[3] = setingSizeOfStringToRect("BACK",pMenu->MenuPlasment[2],TILE_SIZE,TILE_SIZE);
    pMenu->pMenuOptions[2] = makeStringInToSDL_Texture("Select character",pMenu->pFont,pRenderer);
    pMenu->MenuPlasment[3] = (SDL_Point){1,1};
    pMenu->rect[4] = setingSizeOfStringToRect("Select character",pMenu->MenuPlasment[3],TILE_SIZE,TILE_SIZE);
    pMenu->pMenuOptions[3] = makeStringInToSDL_Texture("Create map",pMenu->pFont,pRenderer);
    pMenu->MenuPlasment[4] = (SDL_Point){1,3};
    pMenu->rect[5] = setingSizeOfStringToRect("Create map",pMenu->MenuPlasment[4],TILE_SIZE,TILE_SIZE);
    pMenu->pMenuOptions[4] = makeStringInToSDL_Texture("New character",pMenu->pFont,pRenderer);
    pMenu->MenuPlasment[5] = (SDL_Point){1,2};
    pMenu->rect[6] = setingSizeOfStringToRect("New character",pMenu->MenuPlasment[5],TILE_SIZE,TILE_SIZE);
    pMenu->pMenuOptions[5] = makeStringInToSDL_Texture("DONE",pMenu->pFont,pRenderer);
    pMenu->MenuPlasment[6] = (SDL_Point){1,9};
    pMenu->rect[7] = setingSizeOfStringToRect("DONE",pMenu->MenuPlasment[6],TILE_SIZE,TILE_SIZE);
    pMenu->pMenuOptions[6] = makeStringInToSDL_Texture("< >",pMenu->pFont,pRenderer);
    pMenu->MenuPlasment[7] = (SDL_Point){18,0};
    pMenu->rect[8] = setingSizeOfStringToRect("< >",pMenu->MenuPlasment[7],TILE_SIZE,TILE_SIZE); // resize
    pMenu->pMenuOptions[7] = makeStringInToSDL_Texture("QUIT",pMenu->pFont,pRenderer);
    pMenu->MenuPlasment[8] = (SDL_Point){1,14};
    pMenu->rect[9] = setingSizeOfStringToRect("QUIT",pMenu->MenuPlasment[8],TILE_SIZE,TILE_SIZE); 
    for (int i = 0; i < NUMMBER_OF_MENU_OPTIONS-2; i++){
        if(!pMenu->pMenuOptions[i]){
            fprintf(stderr,"Error creating textrer for menu text (%d):%s",i,SDL_GetError());
            return NULL;
        }
    }
    
    return pMenu;
}

SDL_Rect setingSizeOfStringToRect(char string[NAME],SDL_Point startingPoint,int h,int w){
    SDL_Rect rect;
    rect.x =startingPoint.x * w;
    rect.y =startingPoint.y * h;
    rect.h = h;
    rect.w = ((w/2) *strlen(string));
    return rect;
}

SDL_Texture* makeStringInToSDL_Texture(char string[NAME], TTF_Font *pFont,SDL_Renderer* pRendererer){
    char stringBuff[128];
    snprintf(stringBuff,sizeof(stringBuff),"%s",string);
    SDL_Color color ={255,255,255,255};
    SDL_Surface* pSolidString = TTF_RenderText_Solid(pFont,stringBuff,color);
    SDL_Texture* pTextureString = SDL_CreateTextureFromSurface(pRendererer,pSolidString);
    SDL_FreeSurface(pSolidString);
    return pTextureString;
}

void renderMenu(SDL_Renderer *pRenderer, Menu *pMenu){
    SDL_RenderCopy(pRenderer,pMenu->pBackTextur,NULL,&pMenu->rect[0]);
    if(pMenu->pBoolien->isWriting){
        SDL_SetRenderDrawColor(pRenderer,0,0,0,75);
        SDL_RenderFillRect(pRenderer, &pMenu->rect[1]);
        SDL_RenderCopy(pRenderer,pMenu->playerName,NULL,&pMenu->rect[1]);
    }
    for (int i = 0; i < NUMMBER_OF_MENU_OPTIONS-2; i++){
        SDL_RenderCopy(pRenderer,pMenu->pMenuOptions[i],NULL,&pMenu->rect[i+2]);
    }
    if(pMenu->highlight_rect != 0){
        SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);  // Red
        SDL_RenderDrawRect(pRenderer, &pMenu->rect[pMenu->highlight_rect]);
        SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255); 
    }
}

void updateMenu(SDL_Renderer *pRenderer,Menu *pMenu){
    pMenu->playerName = makeStringInToSDL_Texture(pMenu->stringPlayerName,pMenu->pFont,pRenderer);
    if(pMenu->pBoolien->isChoosingCharacter){
        //render list of Carecters ######################################
    }
    if(pMenu->pBoolien->isDone && pMenu->pBoolien->isWriting){
        if(pMenu->pBoolien->isCreatingCarecter){

        }else{//creating map (done white naming rome)
            pMenu->pBoolien->isOpen = false;
            pMenu->pBoolien->isMakingMap = true;
        }
    }
}

void inputForMenu(Menu *pMenu, SDL_Event event,ScreenAndInput *pControls, bool *pGame,SDL_Window *pWindow,Map *pMap){
    //SDL_ShowCursor(SDL_ENABLE);
    SDL_Point mouse;
    Uint32 mouseState = SDL_GetMouseState(&mouse.x, &mouse.y);
    switch (event.type){
    case SDL_QUIT: 
        pMenu->pBoolien->isOpen = false;
        pControls->keys[SDL_SCANCODE_ESCAPE] = true;
        break;
    case SDL_MOUSEBUTTONDOWN:
        pControls->keys[event.button.state] = SDL_PRESSED;
        //if (event.button.button == SDL_BUTTON_LEFT) pControls->keys[SDL_BUTTON_LEFT] = true; 
        break;
    case SDL_MOUSEBUTTONUP:
        pControls->keys[event.button.state] = SDL_RELEASED;
        //if (event.button.button == SDL_BUTTON_LEFT) pControls->keys[SDL_BUTTON_LEFT] = false; 
        break;
    default:
        break;
    }
    for (int i = 2; i < NUMMBER_OF_MENU_OPTIONS; i++){ //starting on 2 (streng och bracrgrund)
        if(pointInRect(pMenu->rect[i],mouse)){
            pMenu->highlight_rect = i;
            if(mouseState){
                pControls->keys[SDL_BUTTON_LEFT] = false;
                switch (i){
                case 8: //< > 
                    if(pControls->deltaTimeResize <= 2000) return;
                    if (SDL_GetWindowFlags(pWindow) & SDL_WINDOW_FULLSCREEN){
                        SDL_SetWindowFullscreen(pWindow, 0);  // Switch back to windowed mode
                    }else{
                        SDL_SetWindowFullscreen(pWindow, SDL_WINDOW_FULLSCREEN);  // Fullscreen mode
                    }
                    updateTileSizeForMenu(pWindow,pMap,pMenu,pControls->pCamera);
                    pControls->deltaTimeResize = 0;
                    break;
                case 6: //crating carecter
                    pMenu->pBoolien->isWriting = true; 
                    break;
                case 9: //Quting 
                    pMenu->pBoolien->isOpen = false;
                    pControls->keys[SDL_SCANCODE_ESCAPE] = true;
                    break;
                case 5:
                    pMenu->pBoolien->isWriting = true;
                    break;
                case 7: 
                    pMenu->pBoolien->isDone = true;
                    break;
                case 2:
                    pMenu->pBoolien->isOpen = false;
                    break;
                default:
                    break;
                }
            }
            break;
        }else{
            pMenu->highlight_rect = 0;
        }
    }
    if (pMenu->pBoolien->isWriting){
        switch (event.type){
            case SDL_TEXTINPUT:
                //if(pControls->keys[SDL_SCANCODE_0]) pMenu->pBoolien->isOpen = false;
                // Handling backspace (DELETE)
                if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.scancode == SDL_SCANCODE_BACKSPACE && strlen(pMenu->stringPlayerName) > 0) {
                        pMenu->stringPlayerName[strlen(pMenu->stringPlayerName) - 1] = '\0'; // Remove last character
                        pMenu->leter = (pMenu->leter > 0) ? pMenu->leter - 1 : 0;
                        pMenu->rect[1].w = 15 + (pMenu->leter * 15);
                    }
                }
                // Append new text from SDL_TEXTINPUT
                strcat(pMenu->stringPlayerName, event.text.text); 
                pMenu->leter++;
                pMenu->rect[1].w = 15 + (pMenu->leter * 15);
                break;
            case SDL_KEYDOWN: pControls->keys[event.key.keysym.scancode] = true; break;
            case SDL_KEYUP: pControls->keys[event.key.keysym.scancode] = false; break;
        default:
            break;
        }
        if ( pControls->keys[SDL_SCANCODE_BACKSPACE] && strlen(pMenu->stringPlayerName) > 0) {
            pMenu->stringPlayerName[strlen(pMenu->stringPlayerName) - 1] = '\0'; // Remove last character
            pMenu->leter = (pMenu->leter > 0) ? pMenu->leter - 1 : 0;
            pMenu->rect[1].w = 15 + (pMenu->leter * 15);
        }
        if(pControls->keys[SDL_SCANCODE_RETURN]) pMenu->pBoolien->isDone = true;
        if(pControls->keys[SDL_SCANCODE_ESCAPE]) pGame = false;
    }
    
}

void updateTileSizeForMenu(SDL_Window *pWindow,Map *pMap,Menu *pMenu,Camera *pCamera){ 
    int width, height;
    SDL_GetWindowSize(pWindow, &width, &height);
    int tmp = width/VISIBLE_WINDOW_X;
    pMap->TILE_SIZE_W = tmp;
    int tmp1 = height/VISIBLE_WINDOW_Y;
    pMap->TILE_SIZE_H = tmp1;
    //updating menu
    //backgrund
    pMenu->rect[0].h = height;
    pMenu->rect[0].w = width;
    //string
    pMenu->rect[1] = setingSizeOfStringToRect("?string?",pMenu->MenuPlasment[0],
                                            pMap->TILE_SIZE_H,pMap->TILE_SIZE_W); 
    //play
    pMenu->rect[2] = setingSizeOfStringToRect("play",pMenu->MenuPlasment[1],
                                            pMap->TILE_SIZE_H,pMap->TILE_SIZE_W); 
    //back
    pMenu->rect[3] = setingSizeOfStringToRect("back",pMenu->MenuPlasment[2],
                                            pMap->TILE_SIZE_H,pMap->TILE_SIZE_W); 
    //Select character
    pMenu->rect[4] = setingSizeOfStringToRect("Select character",pMenu->MenuPlasment[3],
                                            pMap->TILE_SIZE_H,pMap->TILE_SIZE_W); 
    //Create map
    pMenu->rect[5] = setingSizeOfStringToRect("Create map",pMenu->MenuPlasment[4],
                                            pMap->TILE_SIZE_H,pMap->TILE_SIZE_W); 
    //New character
    pMenu->rect[6] = setingSizeOfStringToRect("New character",pMenu->MenuPlasment[5],
                                            pMap->TILE_SIZE_H,pMap->TILE_SIZE_W); 
    //DONE
    pMenu->rect[7] = setingSizeOfStringToRect("DONE",pMenu->MenuPlasment[6],
                                            pMap->TILE_SIZE_H,pMap->TILE_SIZE_W); 
    //< >
    pMenu->rect[8] = setingSizeOfStringToRect("< >",pMenu->MenuPlasment[7],
                                            pMap->TILE_SIZE_H,pMap->TILE_SIZE_W); 
    //Quit
    pMenu->rect[9] = setingSizeOfStringToRect("QUIT",pMenu->MenuPlasment[8],
                                            pMap->TILE_SIZE_H,pMap->TILE_SIZE_W); 
    //updating map
    updatCurentMap(pMap);
    //also updeting camer pos 
    pCamera->curentPos.x = width/2;
    pCamera->curentPos.y = height/2;
    //updatePlayerSize(pGame->pPlayer,pGame->pMap,pGame->pCamera->curentPos);
}