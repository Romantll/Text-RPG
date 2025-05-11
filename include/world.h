// include/world.h

#ifndef WORLD_H
#define WORLD_H

struct NPC;

typedef struct Room {
    const char *id;
    const char *description;

    struct Room* north;
    struct Room* south;
    struct Room* east;
    struct Room* west;
    struct Room* up;
    struct Room* down;
    struct NPC* npcs; // Pointer to an NPC in the room
} Room;

void addNPCToRoom(Room* room, struct NPC* npc);
Room* createRoom(const char* id, const char* description);
void linkRooms(Room* a, Room* b, const char* direction);
void describeRoom(Room* room);
Room* findRoomById(const char* id);

#endif 