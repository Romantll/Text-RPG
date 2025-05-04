// src/player.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/player.h"

Player createPlayer(Room* startRoom) {
    Player p;
    p.currentRoom = startRoom;
    p.inventory = NULL; 
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
    else if (strcmp(direction, "up") == 0) {
        dest = player->currentRoom->up;
    } else if (strcmp(direction, "down") == 0) {
        dest = player->currentRoom->down;
    } else {
        printf("Invalid direction: %s\n", direction);
        return;
    }
    
    if (dest) {
        player->currentRoom = dest;
        printf("You move %s to the %s.\n", direction, dest->id);
    } else {
        printf("You can't go %s. There's nothing that way.\n", direction);
    }
}