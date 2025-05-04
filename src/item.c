#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/item.h"
#include "../include/player.h"

Item* createItem(int id, const char* name, const char* desc, int damage, int armor, int healing)
{
    Item* item = malloc(sizeof(Item));
    item->id = id;
    item->name  = name;
    item->description = desc;
    item->damage = damage;
    item->armor = armor;
    item->healing = healing;
    item->equipped = 0;
    item->next = NULL;
    return item;
}


Item* createWorldItem(int id){
    switch (id) {
        case 1:
            return createItem(1, "Iron Sword", "A basic iron sword.", 5, 0, 0);
        case 2:
            return createItem(2, "Potion", "Heals you for 25 HP.", 0, 0, 25);
        case 3:
            return createItem(3, "Leather Armor", "Basic leather chestplate.", 0, 5, 0);
        default:
            return NULL; // Invalid item ID
    }
    
}

void addItem(Item** inventory, Item* newItem)
{
    if (!newItem)
    {
        printf("[ERROR] Cannot add NULL item to inventory.\n");
        return;
    }
    
    newItem->next = *inventory;
    *inventory = newItem;
}

void listInventory(Item* inventory)
{
    if (!inventory) {
        printf("Inventory is empty.\n");
        return;
    }

    printf("Your inventory:\n");
    int count = 1;
    while (inventory) {
        printf(" %d. %s", count++, inventory->name);
        if (inventory->equipped) {
            printf(" (equipped)");
        }
        if (inventory->damage > 0) {
            printf(" [Damage: %d]", inventory->damage);
        }
        if (inventory->armor > 0) {
            printf(" [Armor: %d]", inventory->armor);
        }
        if (inventory->healing > 0) {
            printf(" [Healing: %d]", inventory->healing);
        }
        printf("\n");
        inventory = inventory->next;
    }
}

int dropItem(Item** inventory, const char* name) {
    Item* current = *inventory;
    Item* previous = NULL;

    while (current != NULL) {
        if (strcmp(current -> name, name)==0) {
            if (previous == NULL) {
                *inventory = current->next; // Remove the first item
            } else {
                previous->next = current->next; // Remove the item from the list
            }

            free(current); // Free the memory of the dropped item
            printf("You dropped %s.\n", name);
            return 1; // Item was found and removed
        }

        previous = current;
        current = current->next; 
    }
    printf("Item not found in inventory.\n");
    return 0; 
}

void equipItem(Player* player, const char* itemName) {
    Item* item = findItem(player->inventory, itemName);
    if (!item) {
        printf("You don't have that item.\n");
        return;
    }

    if (item->damage > 0) {
        if (player->equippedWeapon) {
            player->equippedWeapon->equipped = 0;
            printf("You unequip %s.\n", player->equippedWeapon->name);
        }
        player->equippedWeapon = item;
        item->equipped = 1;
        printf("You equip %s as your weapon.\n", item->name);
    } else if (item->armor > 0) {
        if (player->equippedArmor) {
            player->equippedArmor->equipped = 0;
            printf("You unequip %s.\n", player->equippedArmor->name);
        }
        player->equippedArmor = item;
        item->equipped = 1;
        printf("You equip %s as your armor.\n", item->name);
    } else {
        printf("You can't equip that item.\n");
    }
}

Item* findItem(Item* inventory, const char* name) {
    while (inventory != NULL) {
        if (strcmp(inventory->name, name) == 0) {
            return inventory; // Item found
        }
        inventory = inventory->next; // Move to the next item
    }
    return NULL; // Item not found
}

Item* getEquippedWeapon(Item* inventory){
    while (inventory != NULL) {
        if (inventory->equipped && inventory->damage > 0) {
            return inventory; // Return the equipped weapon
        }
        inventory = inventory->next; // Move to the next item
    }
    return NULL; // No equipped weapon found
}

Item* getEquippedArmor(Item* inventory){
    while (inventory != NULL) {
        if (inventory->equipped && inventory->armor > 0) {
            return inventory; // Return the equipped armor
        }
        inventory = inventory->next; // Move to the next item
    }
    return NULL; // No equipped armor found
}