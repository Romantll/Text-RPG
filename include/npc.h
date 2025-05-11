#include "player.h"
#ifndef NPC_H
#define NPC_H

typedef enum {
    NPC_FRIENDLY,
    NPC_HOSTILE,
    NPC_MERCHANT,
    NPC_NEUTRAL
} NPCType;

typedef enum {
    COMBAT_CONTINUE,
    COMBAT_WON,
    COMBAT_LOST,
    COMBAT_FLED
}CombatResult;

typedef struct NPC {
    const char* name;
    const char* dialogue;
    NPCType type;

    int hp;
    int maxHp;
    int damage;
    int defense;
    int xpReward;

    struct NPC* next; 
}NPC;

NPC* createNPC(const char* name, const char* dialogue, NPCType type);
NPC* createHostileNPC(const char* name,const char* dialogue, int hp, int damage, int defense, int xpReward);
void fightNPC(Player* player, NPC* npc);
CombatResult fight(Player* player, NPC* npc);
#endif // NPC_H