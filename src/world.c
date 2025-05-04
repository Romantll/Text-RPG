// src/world.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/world.h"


Room* createRoom(const char* id, const char* description) {
    Room* r = malloc(sizeof(Room));
    if (!r) {
        fprintf(stderr, "Failed to allocate memory for room\n");
        exit(1);
    }

    r->id = id;
    r->description = description;

    r->north = r->south = r->east = r->west = r->up = r->down = NULL;
    r->npcs = NULL; // start with no NPCs in the room

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
    else if (strcmp(direction, "up") == 0) {
        a->up = b;
        b->down = a;
    } else if (strcmp(direction, "down") == 0) {
        a->down = b;
        b->up = a;
    } else {
        fprintf(stderr, "Invalid direction: %s\n", direction);
    }
}