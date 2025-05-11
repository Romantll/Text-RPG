#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/save_load.h"
#include "../include/item.h"
#include "../include/world.h"

void saveGame(Player* player, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file for saving");
        return;
    }

    fprintf(file, "room: %s\n", player->currentRoom->id);
    fprintf(file, "health: %d\n", player->hp);
    fprintf(file, "maxHP: %d\n", player->maxHp);
    fprintf(file, "level: %d\n", player->level);
    fprintf(file, "exp: %d\n", player->xp);

    if(player->equippedWeapon)
        fprintf(file, "equippedWeapon: %s\n", player->equippedWeapon->name);
    if(player->equippedArmor)
        fprintf(file, "equippedArmor: %s\n", player->equippedArmor->name);

    fprintf(file, "inventory: ");
    Item* item = player->inventory;
    while (item) {
        fprintf(file, "%s%s", item->name, item->next ? "," : "\n");
        item = item->next;
    }

    fclose(file);
    printf("Game saved to %s\n", filename);
}

int loadGame(Player* player, const char* filename){
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file for loading");
        return 0;
    }

    char line[256];
    char key[64], value[192];

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%[^:]: %[^\n]", key, value) != 2) {
            continue; // Skip invalid lines
        }


        if (strcmp(key, "room") == 0) {
            Room* foundRoom = findRoomById(value); 
            if (foundRoom) player->currentRoom = foundRoom;
        }else if (strcmp(key, "health") == 0) {
            player->hp = atoi(value);
        }else if (strcmp(key, "maxHP") == 0) {
            player->maxHp = atoi(value);
        }else if (strcmp(key, "level") == 0) {
            player->level = atoi(value);
        }else if (strcmp(key, "xp") == 0) {
            player->xp = atoi(value);
        }else if (strcmp(key, "equippedWeapon") == 0) {
            Item* weap = findItem(player->inventory, value);
            if (weap) {
                player->equippedWeapon = weap;
                weap->equipped = 1;
            }
        }else if (strcmp(key, "equippedArmor") == 0) {
            Item* arm = findItem(player->inventory, value);
            if (arm) {
                player->equippedArmor = arm;
                arm->equipped = 1;
            }
        }else if (strcmp(key, "inventory") == 0) {
            player->inventory = NULL;
            char* token = strtok(value, ",");
            while (token) {
                Item* worldItem = createWorldItemByName(token);
                if (worldItem) addItem(&player->inventory, worldItem);
                token = strtok(NULL, ",");
            }
        }
    }
    fclose(file);
    printf("Game loaded from %s\n", filename);
    return 1;
}