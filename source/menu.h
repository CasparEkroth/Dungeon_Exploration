#ifndef MENU_H
#define MENU_H
#include "player.h"

#define NUMMBER_OF_MENU_OPTIONS 8


typedef struct {
    char stringPlayerName[NAME];
    SDL_Texture *playerName;
    int leter;
    TTF_Font *pFont;
    SDL_Rect rect[NUMMBER_OF_MENU_OPTIONS];
    bool open;
}Menu;

Menu* initialize_Menu(SDL_Renderer *pRenderere);

SDL_Texture* makeStringInToSDL_Texture(char string[NAME], TTF_Font *pFont,SDL_Renderer* pRendererer);

void renderMenu(SDL_Renderer *pRenderer, Menu *pMenu);


#endif