// src/world.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/world.h"
#include "../include/npc.h"

#define MAX_ROOMS 100 

static Room* allRooms[MAX_ROOMS];
static int roomCount = 0;

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

    if (roomCount < MAX_ROOMS) {
        allRooms[roomCount++] = r;
    } else {
        printf("Room limit reached. Cannot add more rooms.\n");
     }
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
 void describeRoom(Room* room) {
    printf("You are in %s.\n", room->id);
    printf("%s\n", room->description);

    struct NPC* npc = room->npcs;
    if (npc) {
        printf("You see:\n");
        while (npc) {
            printf(" - %s\n", npc->name);
            npc = npc->next;
        }
    }
 }

 Room* findRoomById(const char* id) {
    for (int i = 0; i < roomCount; i++) {
        if (strcmp(allRooms[i]->id, id) == 0) {
            return allRooms[i];
        }
    }
    return NULL;
 }