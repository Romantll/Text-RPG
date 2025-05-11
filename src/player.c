// src/player.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/player.h"
#include "../include/world.h"

Player createPlayer(struct Room* startRoom) {
    Player p;
    p.currentRoom = startRoom;
    p.inventory = NULL; 
    p.equippedWeapon = NULL;
    p.equippedArmor = NULL;
    p.level = 1; // Starting level
    p.xp = 0; // Starting XP
    p.xpToNextLevel = 75;

    p.hp = 100; // Starting HP
    p.maxHp = 100; // Max HP
    p.baseDamage = 1;
    p.baseDefense = 1;
    return p;
}

void movePlayer(Player* player, const char* direction) {
    struct Room* dest = NULL;
    if (strcmp(direction, "north") == 0) {
        dest = player->currentRoom->north;
    } else if (strcmp(direction, "south") == 0) {
        dest = player->currentRoom->south;
    } else if (strcmp(direction, "east") == 0) {
        dest = player->currentRoom->east;
    } else if (strcmp(direction, "west") == 0) {
        dest = player->currentRoom->west;
    }
    else if (strcmp(direction, "up") == 0) {
        dest = player->currentRoom->up;
    } else if (strcmp(direction, "down") == 0) {
        dest = player->currentRoom->down;
    } else {
        printf("Invalid direction: %s\n", direction);
        return;
    }
    
    if (dest) {
        player->currentRoom = dest;
        printf("You move %s to the %s.\n", direction, dest->id);
    } else {
        printf("You can't go %s. There's nothing that way.\n", direction);
    }
}

void gainXP(Player* player, int amount) {
    player->xp += amount;
    printf("You gain %d XP!\n", amount);

    while (player->xp >= player->xpToNextLevel) {
        player->xp -= player->xpToNextLevel;
        player->level++;
        player->xpToNextLevel = 50 + (player->level * 25);
        player->maxHp += 10; // Increase max HP on level up
        player->hp = player->maxHp; 
        player->baseDamage += 1;
        player->baseDefense += 1;
        printf("You leveled up! You are now level %d!\n", player->level);
    }
}

void showStats(Player* player) {
    printf("\n--- Player Stats ---\n");
    printf("Level: %d\n", player->level);
    printf("XP: %d / %d\n", player->xp, player->xpToNextLevel);
    printf("HP: %d / %d\n", player->hp, player->maxHp);
    printf("Base Damage: %d\n", player->baseDamage);
    printf("Base Defense: %d\n", player->baseDefense);

    if (player->equippedWeapon) {
        printf("Equipped Weapon: %s [+%d]\n", player->equippedWeapon->name, player->equippedWeapon->damage);
    } else {
        printf("Equipped Weapon: None\n");
    }

    if (player->equippedArmor) {
        printf("Equipped Armor: %s [+%d]\n", player->equippedArmor->name, player->equippedArmor->armor);
    } else {
        printf("Equipped Armor: None\n");
    }
    printf("\n");
}
