#include "map.h"

void printMap(char tileMap[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X]){
    for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++){
        for (int x = 0; x < NUMMBER_OF_TILSE_X; x++){
            printf("%c",tileMap[y][x]);
            //printf("%d",tileMap[y][x]);
        }
        printf("\n");
}
}

void trimWhitespace(char *str) {// Ta bort extra whitespace
    char *end;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = 0;
}

void redeFileForMap(char tileMap[NUMMBER_OF_TILSE_Y][NUMMBER_OF_TILSE_X], char fileName[], char newRom[]){
    char buffer[256];
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("Error: Clude not open %s!\n",fileName);
        return;
    }
    while (fgets(buffer, sizeof(buffer), fp)) {
        trimWhitespace(buffer); 
        if (strcmp(buffer, newRom) == 0) {
            for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++) {
                for (int x = 0; x < NUMMBER_OF_TILSE_X; x++) {
                    fscanf(fp, " %c", &tileMap[y][x]);
                }
            }
            break;
        }
    }
    fclose(fp);
    printMap(tileMap);
}

Map *createMap(SDL_Renderer *pRenderre){
    Map *pMap = malloc(sizeof(Map));
    strcpy(pMap->tileRulseFile,"resourses/tileRules.txt");
    strcpy(pMap->curentRoom,"start");
    stpcpy(pMap->mapFile,"resourses/mapFile.txt");
    for (int y = 0; y < NUMMBER_OF_TILSE_Y; y++){
        for (int x = 0; x < NUMMBER_OF_TILSE_X; x++){
            pMap->tileRect[x][y].w = pMap->tileRect[x][y].h = TILE_SIZE;
            pMap->tileRect[x][y].x = x * TILE_SIZE;
            pMap->tileRect[x][y].y = y * TILE_SIZE;
        }
        
    }
    redeFileForMap(pMap->tileMap,pMap->mapFile,pMap->curentRoom);
    
    return pMap;
}