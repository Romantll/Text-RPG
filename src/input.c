#include <stdio.h>
#include <string.h>
#include "../include/input.h"

void getInput(char* buffer, int size) {
    printf("\nWhat do you want to do? ");
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // remove newline
}