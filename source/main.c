#include <SDL.h>
#include "game.h"
int main(){
    printf("Hello,World\n");
    char karta[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X]={0};
    redeFileForMap(karta,"mapFile.txt","rum2");
    printf("\n");
    redeFileForMap(karta,"mapFile.txt","start");
    return 0;
}