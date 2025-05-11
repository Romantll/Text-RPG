#ifndef ITEM_H
#define ITEM_H
typedef struct Player Player;
typedef struct Item {
    int id;
    const char* name;
    const char* description;
    int damage;
    int armor;
    int healing;
    int equipped;
    struct Item* next;
}Item;
Item* createItem(int id, const char* name, const char* description, int damage, int armor, int healing);
Item* createWorldItem(int id);
void addItem(Item** inventory, Item* newitem);
void listInventory(Item* inventory);
int dropItem(Item** inventory, const char* name);
void equipItem(Player* player, const char* itemName);
Item* findItem(Item* inventory, const char* name);
Item* getEquippedWeapon(Item* inventory);
Item* getEquippedArmor(Item* inventory);
void useItem(Player* player, const char* itemName);
Item* createWorldItemByName(const char* name);

#endif // ITEM_H