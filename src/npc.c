#include <stdio.h>
#include <stdlib.h>
#include "../include/npc.h"

NPC* createNPC(const char* name, const char* dialogue, NPCType type) {
    NPC* npc = malloc(sizeof(NPC));
    npc->name = name;
    npc->dialogue = dialogue;
    npc->type = type;
    npc->next = NULL;
    return npc;
}