#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/npc.h"
#include "../include/world.h"
#include "../include/player.h"

NPC* createNPC(const char* name, const char* dialogue, NPCType type) {
    NPC* npc = malloc(sizeof(NPC));
    npc->name = name;
    npc->dialogue = dialogue;
    npc->type = type;
    npc->next = NULL;
    return npc;
}

void addNPCToRoom(Room* room, NPC* npc){
    npc->next = room->npcs;
    room->npcs = npc;
}

void talkToNPC(Player* player, Room* room, const char* npcName){
    NPC* npc = room->npcs;
    while (npc)
    {
        if (strcmp(npc->name, npcName) == 0) {
            printf("%s says: \"%s\"\n", npc->name, npc->dialogue);

            
            if (strcmp(npcName, "Bartender") == 0) 
            {
                if(!findItem(player->inventory, "Iron Sword") && !findItem(player->inventory, "Potion")){
                    printf("The bartender gives you your belongings.\n");
                    printf("The bartender gives you an Iron Sword and a Potion.\n");
                    addItem(&player->inventory, createWorldItem(1)); // Iron Sword
                    addItem(&player->inventory, createWorldItem(2)); // Potion
                    listInventory(player->inventory);
                }else{
                    printf("He already gave you your belongings.\n");
                } 
            }
            return;
    
        }    
        npc = npc->next; 
    }
    printf("You don't see %s here.\n", npcName);
}