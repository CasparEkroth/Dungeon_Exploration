#include "player.h"

Player* CreatePlayer(char playerName[NAME]){
    Player *pPlayer = malloc(sizeof(Player));
    lodePlayer(pPlayer,playerName);
    return pPlayer;
}

void lodePlayer(Player *pPlayer,char playerName[NAME]){
    //läs in från fil
}


void getPlayerName(char playerName[NAME]){
    //kskriver till terminalen eller fixar ett intefase där man kan skriva 
}