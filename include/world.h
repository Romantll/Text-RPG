// include/world.h
#include "npc.h"
#ifndef WORLD_H
#define WORLD_H

typedef struct Room {
    const char *id;
    const char *name;
    const char *description;

    struct Room* north;
    struct Room* south;
    struct Room* east;
    struct Room* west;

    NPC* npc; // Pointer to an NPC in the room
} Room;

Room* createRoom(const char* name, const char* id, const char* description);
void linkRooms(Room* a, Room* b, const char* direction);

#endif 