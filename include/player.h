//include "player.h"

#ifndef PLAYER_H
#define PLAYER_H
#include "world.h"
#include "item.h"

typedef struct Player {
    Room* currentRoom;
    Item* inventory; 
    Item* equippedWeapon; 
    Item* equippedArmor;
}Player;

Player createPlayer(Room* startRoom);
void movePlayer(Player* player, const char* direction);
void talkToNPC(Player* player, Room* room, const char* npcName);

#endif // PLAYER_H