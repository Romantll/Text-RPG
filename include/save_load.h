#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

#include "player.h"

void saveGame(Player* player, const char* filename);
int loadGame(Player* player, const char* filename);

#endif // SAVE_LOAD_H
