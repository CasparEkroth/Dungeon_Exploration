#include "game.h"

void gameRun(Game *pGame,SDL_Event event){
    pGame->game_is_running = true;
    while (pGame->game_is_running){
        pGame->pControls->currentTime  = SDL_GetTicks();
        input(pGame,event);
        update(pGame);
        render(pGame);
        pGame->pControls->previousTime = pGame->pControls->currentTime;
        //handel input and uppdate 
    }
    
    
}

void update(Game *pGame){
    pGame->pPlayer->deltaTime += pGame->pControls->currentTime - pGame->pControls->previousTime;
    worldUpdate(pGame);
}

void render(Game *pGame){
    SDL_RenderClear(pGame->pRenderer);
    renderMap(pGame->pRenderer,pGame->pMap);
    rednerPlayer(pGame->pRenderer,pGame->pPlayer,pGame->pCamera->Ofset);
    if(pGame->pPlayer->pInventory->open){
        //render invetory
    }
    SDL_RenderPresent(pGame->pRenderer);
}

void input(Game *pGame, SDL_Event event){
    //SDL_ShowCursor(SDL_DISABLE);
    pGame->pControls->deltaTimeResize += pGame->pControls->currentTime - pGame->pControls->previousTime;
    while (SDL_PollEvent(&event)){
        switch (event.type)
        {
        case SDL_QUIT: 
            pGame->game_is_running = false;
            break;
        case SDL_KEYDOWN:
            pGame->pControls->keys[event.key.keysym.scancode] = true;
            break;
        case SDL_KEYUP:
            pGame->pControls->keys[event.key.keysym.scancode] = false;
            break;
        default:
            break;
        }
    }        
    if(pGame->pPlayer->pInventory->open){
        //intput för inventory

    }else{
        if(pGame->pControls->keys[SDL_SCANCODE_ESCAPE]) pGame->game_is_running = false;
        if(pGame->pControls->keys[SDL_SCANCODE_LEFT])  pGame->pCamera->Ofset.x += (pGame->pMap->TILE_SIZE_W / SLOWNES); 
        if(pGame->pControls->keys[SDL_SCANCODE_RIGHT])  pGame->pCamera->Ofset.x -= (pGame->pMap->TILE_SIZE_W / SLOWNES); 
        if(pGame->pControls->keys[SDL_SCANCODE_UP])  pGame->pCamera->Ofset.y += (pGame->pMap->TILE_SIZE_H / SLOWNES); 
        if(pGame->pControls->keys[SDL_SCANCODE_DOWN])  pGame->pCamera->Ofset.y -= (pGame->pMap->TILE_SIZE_H / SLOWNES); 
        
        
    }
    if(pGame->pControls->keys[SDL_SCANCODE_P]){
        if(pGame->pControls->deltaTimeResize <= 2000) return;
        if (SDL_GetWindowFlags(pGame->pWindow) & SDL_WINDOW_FULLSCREEN){
            SDL_SetWindowFullscreen(pGame->pWindow, 0);  // Switch back to windowed mode
        }else{
            SDL_SetWindowFullscreen(pGame->pWindow, SDL_WINDOW_FULLSCREEN);  // Fullscreen mode
        }
            updateTileSize(pGame);
            pGame->pControls->deltaTimeResize = 0;
    }

}

void worldUpdate(Game *pGame){ // shifting the map
    for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++){
        for (int x = 0; x < NUMMBER_OF_TILSE_X; x++){
            pGame->pMap->tileRect[y][x].x += pGame->pCamera->Ofset.x;
            pGame->pMap->tileRect[y][x].y += pGame->pCamera->Ofset.y;
        }
    }
    pGame->pCamera->curentPos.x += pGame->pCamera->Ofset.x;
    pGame->pCamera->curentPos.y += pGame->pCamera->Ofset.y;
    pGame->pCamera->Ofset.x = 0;
    pGame->pCamera->Ofset.y = 0;
}


int initialize_window(Game *pGame){ // Initialiserar SDL och skapar fönster
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

ScreenAndInput* initialize_input(void){
    ScreenAndInput* pScreenAndInput = malloc(sizeof(ScreenAndInput));
    pScreenAndInput->currentTime = 0;
    pScreenAndInput->previousTime = 0;
    pScreenAndInput->deltaTimeResize = 0;
    return pScreenAndInput;
}

Camera *initialize_camera(void){
    Camera* pCamera = malloc(sizeof(Camera));
    pCamera->Ofset.x = 0;
    pCamera->Ofset.y = 0;
    pCamera->curentPos.x = STARTING_WINDOW_WIDTH/2;
    pCamera->curentPos.y = STARTING_WINDOW_HEIGHT/2;
    return pCamera;
}

void updateTileSize(Game *pGame){ 
    int width, height;
    SDL_GetWindowSize(pGame->pWindow, &width, &height);
    int tmp = width/VISIBLE_WINDOW_X;
    pGame->pMap->TILE_SIZE_W = tmp;
    int tmp1 = height/VISIBLE_WINDOW_Y;
    pGame->pMap->TILE_SIZE_H = tmp1;
    updatCurentMap(pGame->pMap);
    //also updeting camer pos 
    pGame->pCamera->curentPos.x = width/2;
    pGame->pCamera->curentPos.y = height/2;
    updatePlayerSize(pGame->pPlayer,pGame->pMap,pGame->pCamera->curentPos);
}

void closeGame(Game *pGame){
    if(pGame->pPlayer){
        if(pGame->pPlayer->pSprit_shet) SDL_DestroyTexture(pGame->pPlayer->pSprit_shet);
        for (int i = 0; i < MAX_ITEMS; i++){
            free(pGame->pPlayer->pInventory->pItems[i]);
        }
        free(pGame->pPlayer->pInventory);
        free(pGame->pPlayer);
    }
    if(pGame->pMap){
        if(pGame->pMap->pTileShet) SDL_DestroyTexture(pGame->pMap->pTileShet);
        free(pGame->pMap);
    }
    if(pGame->pControls) free(pGame->pControls);
    if(pGame->pCamera) free(pGame->pCamera);
    if (pGame->pRenderer) SDL_DestroyRenderer(pGame->pRenderer);
    if (pGame->pWindow) SDL_DestroyWindow(pGame->pWindow);
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}