//include "player.h"
#include "item.h"
#ifndef PLAYER_H
#define PLAYER_H
struct Room;
typedef struct Player {
    struct Room* currentRoom;
    Item* inventory; 
    Item* equippedWeapon; 
    Item* equippedArmor;

    int level;
    int xp;
    int xpToNextLevel;
    
    int hp;
    int maxHp;

    int baseDamage;
    int baseDefense;
}Player;


Player createPlayer(struct Room* startRoom);
void movePlayer(Player* player, const char* direction);
void talkToNPC(Player* player, struct Room* room, const char* npcName);
void showStats(Player* player);
void gainXP(Player* player, int amount);


#endif // PLAYER_H