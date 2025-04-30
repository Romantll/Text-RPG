// src/player.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/player.h"

Player createPlayer(Room* startRoom) {
    Player p;
    p.currentRoom = startRoom;
    return p;
}

void movePlayer(Player* player, const char* direction) {
    Room* dest = NULL;
    if (strcmp(direction, "north") == 0) {
        dest = player->currentRoom->north;
    } else if (strcmp(direction, "south") == 0) {
        dest = player->currentRoom->south;
    } else if (strcmp(direction, "east") == 0) {
        dest = player->currentRoom->east;
    } else if (strcmp(direction, "west") == 0) {
        dest = player->currentRoom->west;
    }
    
    if (dest) {
        player->currentRoom = dest;
    } else {
        printf("You can't go that way!\n");
    }
}