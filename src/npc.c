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

    npc->hp = 0;
    npc->maxHp = 0;
    npc->damage = 0;
    npc->defense = 0;
    npc->xpReward = 0;
    return npc;
}

NPC* createHostileNPC(const char* name, const char* dialogue, int hp, int damage, int defense, int xpReward) {
    NPC* npc = createNPC(name, dialogue, NPC_HOSTILE);
    npc->name = name;
    npc->dialogue = dialogue;
    npc->type = NPC_HOSTILE;

    npc->hp = hp;
    npc->maxHp = hp;
    npc->damage = damage;
    npc->defense = defense;
    npc->xpReward = xpReward;
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

CombatResult fight(Player* player, NPC* enemy) {
    printf("You engage in combat with %s!\n", enemy->name);

    int defending = 0;

    while (player->hp > 0 && enemy->hp > 0) {
        printf("\nYour HP: %d/%d | %s's HP: %d/%d\n", player->hp, player->maxHp, enemy->name, enemy->hp, enemy->maxHp);
        printf("Choose your action: (1) Attack (2) Defend (3) Flee\n");

        char input[50];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0; // Remove newline character

        if (strcmp(input, "attack") == 0){
            int critChance = rand() % 100 < 10;
            int damage = player->baseDamage;
            if (player->equippedWeapon) damage += player->equippedWeapon->damage;
            if(critChance) damage *= 2;

            enemy->hp -= damage;
            printf("You attack %s for %d damage%s!\n", enemy->name, damage, critChance ? " (Critical Hit!)" : "");
        } else if (strcmp(input, "defend") == 0) {
            printf("You brace yourself for the next attack.\n");
            defending = 1;
        } else if (strcmp(input, "flee") == 0) {
            if (rand() % 100 < 40) {
                printf("You successfully fled from %s!\n", enemy->name);
                return COMBAT_FLED;
            } else {
                printf("You try to flee, but %s doesn't let you!\n", enemy->name);

            }
        }else{
                printf("Invalid action. Try 'attack', 'defend', or 'flee'.\n");
                continue;
        }

        //check if enemy is dead
        if (enemy->hp <= 0) break;

        // Enemy's turn to attack
        int enemyDamage = enemy->damage - player->baseDefense;
        if (player->equippedArmor) enemyDamage -= player->equippedArmor->armor;
        if (enemyDamage < 1) enemyDamage = 1; // No negative damage

        if (defending) {
            enemyDamage /= 2;
            defending = 0;
        }

        player->hp -= enemyDamage;
        printf("%s attacks you for %d damage!\n", enemy->name, enemyDamage);
    }

    if (player->hp <= 0) {
        printf("You have been defeated by %s...\n", enemy->name);
        return COMBAT_LOST;
    } else {
        printf("You have defeated %s!\n", enemy->name);
        gainXP(player, enemy->xpReward);
        return COMBAT_WON;
    }
}
