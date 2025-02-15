#ifndef MENU_H
#define MENU_H
#include "player.h"

#define NUMMBER_OF_MENU_OPTIONS 10


typedef struct {
    char stringPlayerName[NAME];
    SDL_Texture *playerName;// string 
    SDL_Texture *pBackTextur;// bakrungdsbild
    SDL_Texture *pMenuOptions[NUMMBER_OF_MENU_OPTIONS-2];//-back,string
    SDL_Point MenuPlasment[NUMMBER_OF_MENU_OPTIONS-1]; //-back
    int leter,highlight_rect;
    TTF_Font *pFont;
    SDL_Rect rect[NUMMBER_OF_MENU_OPTIONS];
    bool open,isWriting;
}Menu;

Menu* initialize_Menu(SDL_Renderer *pRenderere, SDL_Window *pWindow);

SDL_Texture* makeStringInToSDL_Texture(char string[NAME], TTF_Font *pFont,SDL_Renderer* pRendererer);
SDL_Rect setingSizeOfStringToRect(char string[NAME],SDL_Point startingPoint,int h,int w);


void inputForMenu(Menu *pMenu, SDL_Event event,ScreenAndInput *pControls, bool pGame,SDL_Window *pWindow, Map *pMap);
void updateTileSizeForMenu(SDL_Window *pWindow,Map *pMap,Menu *pMenu,Camera *pCamera);


void renderMenu(SDL_Renderer *pRenderer, Menu *pMenu);


#endif