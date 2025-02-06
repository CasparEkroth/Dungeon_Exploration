#include "menu.h"


Menu* initialize_Menu(SDL_Renderer *pRenderer){
    Menu* pMenu = malloc(sizeof(Menu));
    if(!pMenu){
        fprintf(stderr,"Memory allocation failed for Menu\n");
        return NULL;
    }
    pMenu->leter = 0;
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
    pMenu->playerName = makeStringInToSDL_Texture("0",pMenu->pFont,pRenderer);
    pMenu->open = true;
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
    SDL_RenderCopy(pRenderer,pMenu->playerName,NULL,&pMenu->rect[0]);
}