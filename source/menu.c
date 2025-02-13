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
    for (int i = 0; i < NUMMBER_OF_MENU_OPTIONS; i++){
        pMenu->rect[i] = (SDL_Rect){0,0,0,0};   //fixar sen 
    }
    pMenu->rect[0] = (SDL_Rect){50,50,500,50};

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
    pMenu->rect[1] =(SDL_Rect){0,0,width,height};
    return pMenu;
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
    SDL_RenderCopy(pRenderer,pMenu->pBackTextur,NULL,&pMenu->rect[1]);
    SDL_RenderCopy(pRenderer,pMenu->playerName,NULL,&pMenu->rect[0]);

    if(pMenu->highlight_rect != 0){
        SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);  // Red
        SDL_RenderDrawRect(pRenderer, &pMenu->rect[pMenu->highlight_rect]);
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255); 
    }
}


void inputForMenu(Menu *pMenu, SDL_Event event,ScreenAndInput *pControls, bool *pGame){
    //SDL_ShowCursor(SDL_ENABLE);
    int mouseX, mouseY;
    SDL_Point mouse;
    Uint32 mouseState = SDL_GetMouseState(&mouse.x, &mouse.y);
    
    switch (event.type){
    case SDL_QUIT: 
        pMenu->open = false;
        pGame = false;
        break;
    case SDL_MOUSEBUTTONDOWN:
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
                //kanpp input för den spesefika rutna 
            }
            break;
        }else{
            pMenu->highlight_rect = 0;
        }
    }
    
}