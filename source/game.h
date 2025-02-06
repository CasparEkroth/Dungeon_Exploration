#ifndef GAME_H
#define GAME_H
#include "player.h"

#define STARTING_WINDOW_WIDTH (TILE_SIZE*20)
#define STARTING_WINDOW_HEIGHT (TILE_SIZE*15)

#define SLOWNES 15
#define NUMMBER_OF_MENU_OPTIONS 8

typedef struct {
    Uint32 currentTime;
    Uint32 previousTime;
    bool keys[SDL_NUM_SCANCODES];
    int deltaTimeResize;
}ScreenAndInput;

typedef struct {
    SDL_Point Ofset,curentPos;
}Camera;

typedef struct {
    char playerName[NAME];
    int leter;
    TTF_Font *pFont;
    SDL_Rect rect[NUMMBER_OF_MENU_OPTIONS];
    bool open;
}Menu;


typedef struct {
    Player *pPlayer;
    Camera *pCamera;
    ScreenAndInput *pControls;
    Menu *pMenu;
    bool game_is_running;
    SDL_Renderer *pRenderer;
    SDL_Window *pWindow;
    Map *pMap;
    //Enemy
}Game;




int initialize_window(Game *pGame);
ScreenAndInput* initialize_input(void);
Camera *initialize_camera(void);
Menu* initialize_Menu(void);

void closeGame(Game *pGame);

void inputForKebord(Game *pGame);


void gameRun(Game *pGame,SDL_Event event);

void input(Game *pGame, SDL_Event event);
void render(Game *pGame);
void update(Game *pGame);


void worldUpdate(Game *pGame);
void updateTileSize(Game *pGame);



#endif 