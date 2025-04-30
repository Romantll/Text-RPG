//include "player.h"

#ifndef PLAYER_H
#define PLAYER_H
#include "world.h"

typedef struct{
    Room* currentRoom;
}Player;

Player createPlayer(Room* startRoom);
void movePlayer(Player* player, const char* direction);

#endif // PLAYER_H