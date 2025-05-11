#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/world.h"
#include "../include/player.h"
#include "../include/npc.h"
#include "../include/input.h"
#include "../include/item.h"
#include "../include/save_load.h"


int main (void)
{
    // Create rooms
   Room* starterRoom = createRoom(
        "Player Room",
        "You are in a small cozy room on the second floor. There's a door to the south."
    );
    
    Room* hallway2F = createRoom(
        "Second Floor Hallway",
        "A long hallway, doors line either side. To the east is the staircase it leads downstairs, and your room is to the north."
    );

    Room* commonRoom = createRoom(
        "Common Room",
        "A common room with a couple of benches and bookshelves lining the walls. Two strangers are sitting down. There's a door to the west, and stairs leading upstairs."
    );

    Room* mainHall = createRoom(
        "Main Hall",
        "The heart of the inn, bustling with activity. To the west is the bar, to the north is the kitchen, and to the east is the common area"
    );

    Room* kitchen = createRoom(
        "Kitchen",
        "A large kitchen with with a couple employees cooking. There seems to be a door to the east leading donwstairs."
    );

    Room* outsideInn = createRoom(
        "Outside Inn",
        "The outside of the inn."
    );
    linkRooms(starterRoom, hallway2F, "south");
    linkRooms(hallway2F, commonRoom, "down");
    linkRooms(commonRoom, mainHall, "west");
    linkRooms(mainHall, kitchen, "north");
    linkRooms(mainHall, outsideInn, "south");
    Player player = createPlayer(starterRoom); // Create the player in the starter room
    
    NPC* reader = createNPC("Scholar", "Nothing like a good book to pass the time.", NPC_FRIENDLY);
    NPC* drinker = createNPC("Wanderer", "Nothing like a good drink to warm the soul.", NPC_FRIENDLY);
    NPC* bartender = createNPC("Bartender", "Good morning travler. Here is your stuff.", NPC_FRIENDLY);
    NPC* bandit = createHostileNPC("Bandit", "Hello friend.", 25, 5, 2, 100);

    addNPCToRoom(commonRoom, reader);
    addNPCToRoom(commonRoom, drinker); 
    addNPCToRoom(mainHall, bartender);
    addNPCToRoom(kitchen, bandit);


    char input[64];

    while (1) {
        describeRoom(player.currentRoom);

        getInput(input, sizeof(input));

        if (strcmp(input, "quit") == 0) {
            printf("Thanks for playing!\n");
            break;
        }

        if (strcmp(input, "north") == 0 || strcmp(input, "n") == 0) {
            movePlayer(&player, "north");
        } else if (strcmp(input, "south") == 0 || strcmp(input, "s") == 0) {
            movePlayer(&player, "south");
        } else if (strcmp(input, "east") == 0 || strcmp(input, "e") == 0) {
            movePlayer(&player, "east");
        } else if (strcmp(input, "west") == 0 || strcmp(input, "w") == 0) {
            movePlayer(&player, "west");
        }else if (strcmp(input, "up") == 0 || strcmp(input, "u") == 0) {
            movePlayer(&player, "up"); 
        }else if (strcmp(input, "down") == 0 || strcmp(input, "d") == 0) {
            movePlayer(&player, "down");
        }else if (strcmp(input, "inventory") == 0) {
            listInventory(player.inventory);
        } else if (strncmp(input, "equip ", 6) == 0) {
            equipItem(&player, input + 6); // Pass the item name after "equip "
        }else if (strncmp(input, "talk ", 5)==0){
            talkToNPC(&player, player.currentRoom, input + 5);
        }else if (strncmp(input, "use ", 4) == 0) {
            useItem(&player, input + 4);   
        }else if (strcmp(input, "stats") == 0) {
            showStats(&player);    
        }else if (strcmp(input, "save") == 0) {
            saveGame(&player, "savefile.txt");
        }else if (strcmp(input, "load") == 0) {
            loadGame(&player, "savefile.txt");
        }else if (strncmp(input, "attack ", 7) == 0) {
            char* target = input + 7;
            NPC* npc = player.currentRoom->npcs;

            while (npc) {
                if (strcmp(npc->name, target) == 0) {
                    CombatResult result = fight(&player, npc);

                    if (result == COMBAT_WON) {
                        
                        NPC** current = &player.currentRoom->npcs;
                        while (*current)
                        {
                            *current = npc->next;
                            free(npc);
                             printf("You defeated %s!\n", target);
                            printf("You gain %d XP!\n", npc->xpReward);
                            break;   
                        }
                        current = &(*current)->next;      
                    }
                    break;
                }
            }

            if (!npc) {
                printf("You don't see %s here.\n", target);
            }

        } else {
            printf("I don't understand '%s'. Try north, south, east, west, up, or down.\n", input);
        }
}
    return 0;
}