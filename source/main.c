#include <SDL.h>
#include "game.h"
int main(){
    char karta[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X]={0};
    redeFileForMap(karta,"resourses/mapFile.txt","rum2");
    printf("\n");
    redeFileForMap(karta,"resourses/mapFile.txt","start");
    return 0;
}