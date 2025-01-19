#include "game.h"

void gameRun(Game *pGame,SDL_Event event){
    pGame->game_is_running = true;
    while (pGame->game_is_running){
        input(pGame,event);
        render(pGame);
        //handel input and uppdate 
    }
    
    
}

void render(Game *pGame){
    SDL_RenderClear(pGame->pRenderer);
    renderMap(pGame->pRenderer,pGame->pMap);
    SDL_RenderPresent(pGame->pRenderer);
}


void input(Game *pGame, SDL_Event event){
    SDL_ShowCursor(SDL_DISABLE);
    while (SDL_PollEvent(&event)){
        switch (event.type)
        {
        case SDL_QUIT: 
            pGame->game_is_running = false;
            break;
        case SDL_KEYDOWN:
            pGame->keys[event.key.keysym.scancode] = true;
            break;
        case SDL_KEYUP:
            pGame->keys[event.key.keysym.scancode] = false;
            break;
        default:
            break;
        }
    }
    if(pGame->keys[event.window.event]){
    if (SDL_GetWindowFlags(pGame->pWindow) & SDL_WINDOW_FULLSCREEN){
    SDL_SetWindowFullscreen(pGame->pWindow, 0);  // Switch back to windowed mode
    }else{
        SDL_SetWindowFullscreen(pGame->pWindow, SDL_WINDOW_FULLSCREEN);  // Fullscreen mode
    }
    }
    if(pGame->keys[SDL_SCANCODE_ESCAPE]) pGame->game_is_running = false;
    if(pGame->keys[SDL_SCANCODE_LEFT]){
    }
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
        if(pGame->pMap->pTileShet) SDL_DestroyTexture(pGame->pMap->pTileShet);
        free(pGame->pMap);
    }
    if (pGame->pRenderer) SDL_DestroyRenderer(pGame->pRenderer);
    if (pGame->pWindow) SDL_DestroyWindow(pGame->pWindow);
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

}