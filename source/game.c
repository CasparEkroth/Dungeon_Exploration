#include "game.h"

void gameRun(Game *pGame){
    pGame->game_is_runing = true;
    while (pGame->game_is_runing){
        //render()
        //handel input and uppdate 
    }
    
    initialize_window(pGame);
}

// Initialiserar SDL och skapar fönster
int initialize_window(Game *pGame){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0 || TTF_Init() != 0 || SDL_Init(SDL_INIT_AUDIO) < 0){
        fprintf(stderr, "Error initializing SDL. %s\n", SDL_GetError());
        return false;
    }
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        fprintf(stderr, "Error initializing SDL_image: %s\n", IMG_GetError());
        return false;
    }
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        fprintf(stderr,"SDL_mixer could not initialize! Mix_Error: %s\n",Mix_GetError());
        return false;
    }
    pGame->pWindow = SDL_CreateWindow(
        NULL, // Titel
        SDL_WINDOWPOS_CENTERED, // x
        SDL_WINDOWPOS_CENTERED, // y 
        STARTING_WINDOW_WIDTH, 
        STARTING_WINDOW_HEIGHT, 
        SDL_WINDOW_RESIZABLE  // Flags
    );
    if (!pGame->pWindow) {
        fprintf(stderr, "Error creating SDL Window: %s\n", SDL_GetError());
        return false;
    }

    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    pGame->pRenderer = SDL_CreateRenderer(pGame->pWindow, -1, render_flags);
    if (!pGame->pRenderer) {
        fprintf(stderr, "Error creating SDL Renderer: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

void closeGame(Game *pGame){
    if(pGame->pMap){
        //destroy eventuel texturr 
        free(pGame->pMap);
    }
    if (pGame->pRenderer) SDL_DestroyRenderer(pGame->pRenderer);
    if (pGame->pWindow) SDL_DestroyWindow(pGame->pWindow);
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

}