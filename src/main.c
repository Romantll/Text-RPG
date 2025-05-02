#include <stdio.h>
#include <string.h>
#include "../include/world.h"
#include "../include/player.h"
#include "../include/npc.h"

void getInput(char* buffer, int size) {
    printf("\nWhat do you want to do? ");
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // remove newline
}


int main (void)
{
    // Create rooms
    Room* inn = createRoom("Inn", "Old Inn", "A cozy inn with a warm fireplace.");
    NPC* innkeeper = createNPC("Innkeeper", "Welcome to the Old Inn!", NPC_FRIENDLY);
    inn->npc = innkeeper; // Assign NPC to the room
    Room* livingRoom = createRoom("Living Room", "Living Room", "A spacious living room with a large sofa.");
    Room* bedroom = createRoom("Bedroom", "Bedroom", "A small bedroom with a bed and a wardrobe.");
    
    linkRooms(inn, livingRoom, "north");
    linkRooms(livingRoom, bedroom, "east");

    Player player = createPlayer(inn);
    NPC* current = player.currentRoom->npc; // Get the NPC in the current room
    while (current != NULL) {
        printf("You see %s here. They say: \"%s\"\n", current->name, current->dialogue);
        current = current->next;
    }
    char input[64];

    while (1) {
        printf("You are in the %s.\n", player.currentRoom->name);
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
        } else {
            printf("I don't understand '%s'. Try north, south, east, or west.\n", input);
        }
}
    return 0;
}