#include "menu.h"

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

    pMenu->rect[1] = (SDL_Rect){50,50,500,50}; //koll vart de ska vara 

    pMenu->pFont = TTF_OpenFont("resourses/RubikMaps-Regular.ttf",24);
        if(!pMenu->pFont){
        fprintf(stderr,"Error: Loding font: %s\n", TTF_GetError());
        return false;
    }
    pMenu->playerName = makeStringInToSDL_Texture("",pMenu->pFont,pRenderer);
    pMenu->open = true;
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
    SDL_Point A ={1,3};//x,y
    pMenu->rect[2] = setingSizeOfStringToRect("PLAY",A,TILE_SIZE,TILE_SIZE);
    pMenu->pMenuOptions[1] = makeStringInToSDL_Texture("BACK",pMenu->pFont,pRenderer);
    A = (SDL_Point){1,4};
    pMenu->rect[3] = setingSizeOfStringToRect("BACK",A,TILE_SIZE,TILE_SIZE);
    pMenu->pMenuOptions[2] = makeStringInToSDL_Texture("Select character",pMenu->pFont,pRenderer);
    A = (SDL_Point){1,5};
    pMenu->rect[4] = setingSizeOfStringToRect("Select character",A,TILE_SIZE,TILE_SIZE);
    pMenu->pMenuOptions[3] = makeStringInToSDL_Texture("Create map",pMenu->pFont,pRenderer);
    A = (SDL_Point){1,6};
    pMenu->rect[5] = setingSizeOfStringToRect("Create map",A,TILE_SIZE,TILE_SIZE);
    pMenu->pMenuOptions[4] = makeStringInToSDL_Texture("New character",pMenu->pFont,pRenderer);
    A = (SDL_Point){1,7};
    pMenu->rect[6] = setingSizeOfStringToRect("New character",A,TILE_SIZE,TILE_SIZE);
    pMenu->pMenuOptions[5] = makeStringInToSDL_Texture("DONE",pMenu->pFont,pRenderer);
    A = (SDL_Point){1,9};
    pMenu->rect[7] = setingSizeOfStringToRect("DONE",A,TILE_SIZE,TILE_SIZE);
    pMenu->pMenuOptions[6] = makeStringInToSDL_Texture("< >",pMenu->pFont,pRenderer);
    A = (SDL_Point){18,0};
    pMenu->rect[8] = setingSizeOfStringToRect("< >",A,TILE_SIZE,TILE_SIZE); // resize
    pMenu->pMenuOptions[7] = makeStringInToSDL_Texture("QUIT",pMenu->pFont,pRenderer);
    A = (SDL_Point){10,10};
    pMenu->rect[9] = setingSizeOfStringToRect("QUIT",A,TILE_SIZE,TILE_SIZE); 
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
    SDL_RenderCopy(pRenderer,pMenu->playerName,NULL,&pMenu->rect[1]);
    for (int i = 0; i < NUMMBER_OF_MENU_OPTIONS-2; i++){
        SDL_RenderCopy(pRenderer,pMenu->pMenuOptions[i],NULL,&pMenu->rect[i+2]);
    }
    if(pMenu->highlight_rect != 0){
        SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);  // Red
        SDL_RenderDrawRect(pRenderer, &pMenu->rect[pMenu->highlight_rect]);
        SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255); 
    }
}

void inputForMenu(Menu *pMenu, SDL_Event event,ScreenAndInput *pControls, bool pGame,SDL_Window *pWindow,Map *pMap){
    //SDL_ShowCursor(SDL_ENABLE);
    SDL_Point mouse;
    Uint32 mouseState = SDL_GetMouseState(&mouse.x, &mouse.y);
    
    switch (event.type){
    case SDL_QUIT: 
        pMenu->open = false;
        pGame = false;
        break;
    case SDL_MOUSEBUTTONDOWN:
        break;
    case SDL_MOUSEBUTTONUP:
        break;
    case SDL_TEXTINPUT:
        break;
    default:
        break;
    }
    for (int i = 2; i < NUMMBER_OF_MENU_OPTIONS; i++){ //starting on 2 (streng och bracrgrund)
        if(pointInRect(pMenu->rect[i],mouse)){
            pMenu->highlight_rect = i;
            if(mouseState){
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
                
                default:
                    break;
                }
                //pMenu->rect[i].x += TILE_SIZE; 
            }
            break;
        }else{
            pMenu->highlight_rect = 0;
        }
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
    SDL_Point A ={1,3};//x,y
    pMenu->rect[1] = setingSizeOfStringToRect("?string?",A,pMap->TILE_SIZE_H,pMap->TILE_SIZE_W); 
    //play
    A = (SDL_Point){1,4};
    pMenu->rect[2] = setingSizeOfStringToRect("play",A,pMap->TILE_SIZE_H,pMap->TILE_SIZE_W); 
    //back
    A = (SDL_Point){1,5};
    pMenu->rect[3] = setingSizeOfStringToRect("back",A,pMap->TILE_SIZE_H,pMap->TILE_SIZE_W); 
    //Select character
    A = (SDL_Point){1,6};
    pMenu->rect[4] = setingSizeOfStringToRect("Select character",A,pMap->TILE_SIZE_H,pMap->TILE_SIZE_W); 
    //Create map
    A = (SDL_Point){1,7};
    pMenu->rect[5] = setingSizeOfStringToRect("Create map",A,pMap->TILE_SIZE_H,pMap->TILE_SIZE_W); 
    //New character
    A = (SDL_Point){1,8};
    pMenu->rect[6] = setingSizeOfStringToRect("New character",A,pMap->TILE_SIZE_H,pMap->TILE_SIZE_W); 
    //DONE
    A = (SDL_Point){1,9};
    pMenu->rect[7] = setingSizeOfStringToRect("DONE",A,pMap->TILE_SIZE_H,pMap->TILE_SIZE_W); 
    //< >
    A = (SDL_Point){18,0};
    pMenu->rect[8] = setingSizeOfStringToRect("< >",A,pMap->TILE_SIZE_H,pMap->TILE_SIZE_W); 
    //Quit
    A = (SDL_Point){1,10};
    pMenu->rect[9] = setingSizeOfStringToRect("QUIT",A,pMap->TILE_SIZE_H,pMap->TILE_SIZE_W); 
    //updating map
    updatCurentMap(pMap);
    //also updeting camer pos 
    pCamera->curentPos.x = width/2;
    pCamera->curentPos.y = height/2;
    //updatePlayerSize(pGame->pPlayer,pGame->pMap,pGame->pCamera->curentPos);
}