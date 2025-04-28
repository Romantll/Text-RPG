// include/world.h

#ifndef WORLD_H
#define WORLD_H

typedef struct {
    const char *name;
    struct Room* north;
    struct Room* south;
    struct Room* east;
    struct Room* west;
} Room;

Room* createRoom(const char *name);
void linkRooms(Room* a, Room* b, const char* direction);

#endif 