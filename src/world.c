// src/world.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/world.h"

Room* createRoom(const char* name){
    
    Room* r = malloc(sizeof(Room));
    r->name = name;
    r->north = r->south = r->east = r->west = NULL;
    return r;
}

void linkRooms(Room* a, Room* b, const char* direction){
    if (strcmp(direction, "north") == 0) {
        a->north = b;
        b->south = a;
    } else if (strcmp(direction, "south") == 0) {
        a->south = b;
        b->north = a;
    } else if (strcmp(direction, "east") == 0) {
        a->east = b;
        b->west = a;
    } else if (strcmp(direction, "west") == 0) {
        a->west = b;
        b->east = a;
    }
}