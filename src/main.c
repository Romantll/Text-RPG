#include <stdio.h>
#include "../include/world.h"
#include "../include/player.h"

int main (void)
{
    // Create rooms
    Room* kitchen = createRoom("Kitchen");
    Room* livingRoom = createRoom("Living Room");
    Room* bedroom = createRoom("Bedroom");
    
    linkRooms(kitchen, livingRoom, "north");
    linkRooms(livingRoom, bedroom, "east");

    Player player = createPlayer(kitchen);

    printf("You are in the %s\n", player.currentRoom->name);
    movePlayer(&player, "north");
    printf("You are in the %s\n", player.currentRoom->name);
    movePlayer(&player, "east");
    printf("You are in the %s\n", player.currentRoom->name);
    movePlayer(&player, "west");
    printf("You are in the %s\n", player.currentRoom->name);

    return 0;
}