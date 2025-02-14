#include "game.h"

void gameRun(Game *pGame,SDL_Event event){
    pGame->game_is_running = true;
    while (pGame->game_is_running){
        pGame->pControls->currentTime  = SDL_GetTicks();
        input(pGame,event);
        update(pGame);
        render(pGame);
        pGame->pControls->previousTime = pGame->pControls->currentTime;
    }
}

void update(Game *pGame){
    pGame->pPlayer->deltaTime += pGame->pControls->currentTime - pGame->pControls->previousTime;
    worldUpdate(pGame);
}

void render(Game *pGame){
    SDL_RenderClear(pGame->pRenderer);
    if(pGame->pMenu->open){
        renderMenu(pGame->pRenderer,pGame->pMenu);
    }else{
        renderMap(pGame->pRenderer,pGame->pMap);
        rednerPlayer(pGame->pRenderer,pGame->pPlayer,pGame->pControls->pCamera->Ofset);
        if(pGame->pPlayer->pInventory->open){
            //render invetory
        }
    }
    SDL_RenderPresent(pGame->pRenderer);
}

void input(Game *pGame, SDL_Event event){
    //SDL_ShowCursor(SDL_DISABLE);
    pGame->pControls->pCamera->Ofset.x = 0;
    pGame->pControls->pCamera->Ofset.y = 0;
    pGame->pControls->deltaTimeResize += pGame->pControls->currentTime - pGame->pControls->previousTime;
    if(pGame->pMenu->open){
        inputForMenu(pGame->pMenu,event,pGame->pControls,pGame->game_is_running,pGame->pWindow,pGame->pMap);
    }
    while (SDL_PollEvent(&event)){
        switch (event.type){
        case SDL_QUIT: 
            pGame->game_is_running = false;
            break;
        case SDL_KEYDOWN:
            pGame->pControls->keys[event.key.keysym.scancode] = true; //kan man göra till en funktion 
            break;
        case SDL_KEYUP:
            pGame->pControls->keys[event.key.keysym.scancode] = false;
            break;
        case SDL_TEXTINPUT:
            if(pGame->pControls->keys[SDL_SCANCODE_0]) pGame->pMenu->open = false;
            if(pGame->pControls->keys[SDL_SCANCODE_ESCAPE]) pGame->game_is_running = false;
            if(pGame->pControls->keys[SDL_SCANCODE_BACKSPACE]){
                pGame->pMenu->stringPlayerName[strlen(pGame->pMenu->stringPlayerName)-1] = ' ';
            }
            if(pGame->pMenu->open){//text handler 
                strcat(pGame->pMenu->stringPlayerName,event.text.text); 
                pGame->pMenu->playerName = makeStringInToSDL_Texture(pGame->pMenu->stringPlayerName,pGame->pMenu->pFont,pGame->pRenderer);
                pGame->pMenu->leter++;
                pGame->pMenu->rect[1].w = 15+(pGame->pMenu->leter*15);
            }
            break;
        default:
            break;
        }
    }        
    if(pGame->pPlayer->pInventory->open){
        //intput för inventory

    }else if(pGame->pMenu->open){
        if(pGame->pControls->keys[SDL_SCANCODE_0]) pGame->pMenu->open = false;
    }else{
        if(pGame->pControls->keys[SDL_SCANCODE_ESCAPE]) pGame->game_is_running = false;
        if(pGame->pControls->keys[SDL_SCANCODE_LEFT])  pGame->pControls->pCamera->Ofset.x += (pGame->pMap->TILE_SIZE_W / SLOWNES); 
        if(pGame->pControls->keys[SDL_SCANCODE_RIGHT])  pGame->pControls->pCamera->Ofset.x -= (pGame->pMap->TILE_SIZE_W / SLOWNES); 
        if(pGame->pControls->keys[SDL_SCANCODE_UP])  pGame->pControls->pCamera->Ofset.y += (pGame->pMap->TILE_SIZE_H / SLOWNES); 
        if(pGame->pControls->keys[SDL_SCANCODE_DOWN])  pGame->pControls->pCamera->Ofset.y -= (pGame->pMap->TILE_SIZE_H / SLOWNES); 
        
        if(pGame->pControls->pCamera->Ofset.x != 0 && pGame->pControls->pCamera->Ofset.y != 0){
            pGame->pControls->pCamera->Ofset.x = (pGame->pControls->pCamera->Ofset.x/1.7);
            pGame->pControls->pCamera->Ofset.y = (pGame->pControls->pCamera->Ofset.y/1.7);
        }
    }
    if(pGame->pControls->keys[SDL_SCANCODE_P]){
        if(pGame->pControls->deltaTimeResize <= 2000) return;
        if (SDL_GetWindowFlags(pGame->pWindow) & SDL_WINDOW_FULLSCREEN){
            SDL_SetWindowFullscreen(pGame->pWindow, 0);  // Switch back to windowed mode
        }else{
            SDL_SetWindowFullscreen(pGame->pWindow, SDL_WINDOW_FULLSCREEN);  // Fullscreen mode
        }
            updateTileSizeForMenu(pGame->pWindow,pGame->pMap,pGame->pMenu,pGame->pControls->pCamera);//temporery
            pGame->pControls->deltaTimeResize = 0;
    }
}

void worldUpdate(Game *pGame){ // shifting the map
    for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++){
        for (int x = 0; x < NUMMBER_OF_TILSE_X; x++){
            pGame->pMap->tileRect[y][x].x += pGame->pControls->pCamera->Ofset.x;
            pGame->pMap->tileRect[y][x].y += pGame->pControls->pCamera->Ofset.y;
        }
    }
    pGame->pControls->pCamera->curentPos.x += pGame->pControls->pCamera->Ofset.x;
    pGame->pControls->pCamera->curentPos.y += pGame->pControls->pCamera->Ofset.y;

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
    if(pGame->pControls->pCamera) free(pGame->pControls->pCamera);
    if(pGame->pControls) free(pGame->pControls);
    if(pGame->pMenu){
        if(pGame->pMenu->pFont) TTF_CloseFont(pGame->pMenu->pFont);
        if(pGame->pMenu->playerName) SDL_DestroyTexture(pGame->pMenu->playerName);
        if(pGame->pMenu->pBackTextur) SDL_DestroyTexture(pGame->pMenu->pBackTextur);
        for (int i = 0; i < NUMMBER_OF_MENU_OPTIONS-2; i++){
            if(pGame->pMenu->pMenuOptions[i]) SDL_DestroyTexture(pGame->pMenu->pMenuOptions[i]);
        }
        free(pGame->pMenu);
    }
    if (pGame->pRenderer) SDL_DestroyRenderer(pGame->pRenderer);
    if (pGame->pWindow) SDL_DestroyWindow(pGame->pWindow);
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}