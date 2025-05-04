#include <stdio.h>
#include <string.h>
#include "../include/world.h"
#include "../include/player.h"
#include "../include/npc.h"
#include "../include/input.h"


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
        "A common room with a couple of benches and bookshelves lining the walls. There's a door to the west, and stairs leading upstairs."
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

    addNPCToRoom(commonRoom, reader);
    addNPCToRoom(commonRoom, drinker); 
    addNPCToRoom(mainHall, bartender);

    NPC* current = player.currentRoom->npcs; // Get the NPC in the current room
    while (current != NULL) {
        printf("You see %s here. They say: \"%s\"\n", current->name, current->dialogue);
        current = current->next;
    }

    char input[64];

    while (1) {
        printf("You are in the %s.\n", player.currentRoom->id);
        printf("%s\n", player.currentRoom->description);

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
            equipItem(player.inventory, input + 6); // Pass the item name after "equip "
        }else if (strncmp(input, "talk ", 5)==0){
            talkToNPC(&player, player.currentRoom, input + 5);
        } 
        else {
            printf("I don't understand '%s'. Try north, south, east, or west.\n", input);
        }
}
    return 0;
}